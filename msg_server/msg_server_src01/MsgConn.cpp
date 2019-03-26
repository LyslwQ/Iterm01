#include <muduo/net/Timestamp.h>
#include <muduo/net/EventLoop.h>
#include "MsgConn.h"
#include "DBServConn.h"
#include "LoginServConn.h"
#include "RouteServConn.h"
#include "FileHandler.h"
#include "GroupChat.h"
#include "ImUser.h"
#include "AttachData.h"
#include "IM.Buddy.pb.h"
#include "IM.Message.pb.h"
#include "IM.Login.pb.h"
#include "IM.Other.pb.h"
#include "IM.Group.pb.h"
#include "IM.Server.pb.h"
#include "IM.SwitchService.pb.h"
#include "public_define.h"
#include "ImPduBase.h"
using namespace IM::BaseDefine;

typedef muduo::net::Timestamp Timestamp; //可以实现微妙级的时间记录

#define TIMEOUT_WATI_LOGIN_RESPONSE	15000	// 15 seconds
#define TIMEOUT_WAITING_MSG_DATA_ACK	15000	// 15 seconds
#define LOG_MSG_STAT_INTERVAL		300000	// log message miss status in every 5 minutes;
#define MAX_MSG_CNT_PER_SECOND		20	// user can not send more than 20 msg in one second
extern g_pTimerLoop; //定义在main文件中

static ConnMap_t g_msg_conn_map;
static UserMap_t g_msg_conn_user_map;

static uint64_t	g_last_stat_tick;	        // 上次显示丢包率信息的时间
static uint32_t g_up_msg_total_cnt   = 0;	// 上行消息包总数
static uint32_t g_up_msg_miss_cnt    = 0;	// 上行消息包丢数
static uint32_t g_down_msg_total_cnt = 0;	// 下行消息包总数
static uint32_t g_down_msg_miss_cnt  = 0;	// 下行消息丢包数

static bool g_log_msg_toggle = true; // 是否把收到的MsgData写入Log的开关，通过kill -SIGUSR2 pid 打开/关闭

static CFileHandler* s_file_handler = NULL;
static CGroupChat* s_group_chat = NULL;


void CMsgConn::onMessage(const TcpConnectionPtr& conn,
	                 Buffer* buf,
	                 Timestamp receiveTime)
{ //读取数据
  //解析数据包
  //  //调用Handle
  CImPdu* pPdu = NULL;
  try{
      while ( pPdu = CImPdu::ReadPdu(buf)){
          uint32_t pdu_len = pPdu->GetLength();
         // muduo::MutexLockGuard guard(s_lock);
	  HandlePdu(pPdu);  //pPdu已在此处交给Handler处理（包括生命期）
          pPdu = NULL;
      }
  }
  catch (CPduException& ex) {
      log("!!!catch exception, sid=%u, cid=%u, 
           err_code=%u, err_msg=%s, close the connection ",
	   ex.GetServiceId(), ex.GetCommandId(), ex.GetErrorCode(), ex.GetErrorMsg());
      if (pPdu) {
          delete pPdu;
          pPdu = NULL;
      }
      conn->forceClose();
  }
}



void CMsgConn::onConnection(const TcpConnectionPtr& conn)
{
  if( conn->disconnected())  //连接关闭。
      Close(conn);
}


//用于强制关闭异常连接。
void CMsgConn::forceClose()
{
  m_conn->forceClose();
}

//用于被通知关闭时的处理工作。（即被动关闭）
void CMsgConn::close(const TcpConnectionPtr& conn)
{
  log("Close client, user_id=%u ", GetUserId());
    
  CImUser *pImUser = CImUserManager::GetInstance()->GetImUserById(GetUserId());
  if (pImUser) {
      pImUser->DelMsgConn(GetConn());
      pImUser->DelUnValidateMsgConn(this);
        
      SendUserStatusUpdate(::IM::BaseDefine::USER_STATUS_OFFLINE);
      if (pImUser->IsMsgConnEmpty()) 
          CImUserManager::GetInstance()->RemoveImUser(pImUser);
  }
    
  pImUser = CImUserManager::GetInstance()->GetImUserByLoginName(GetLoginName());
  if (pImUser) {
      pImUser->DelUnValidateMsgConn(this);
      if (pImUser->IsMsgConnEmpty()) 
          CImUserManager::GetInstance()->RemoveImUser(pImUser);
  }
  m_serv_callback(this); //必须最后调用，CMsgConn对象生命期将在该函数中结束。 
}





CMsgConn::OnTimer(int64_t curr_tick)  //t是毫秒
{
  m_msg_cnt_per_sec = 0;
  //连接超时
  if (CHECK_CLIENT_TYPE_MOBILE(GetClientType())){
      if (curr_tick > m_last_recv_tick + MOBILE_CLIENT_TIMEOUT) {
          log("mobile client timeout, uid=%u ", GetUserId());
          forceClose();
          return;
     }
  }
  else{
      if (curr_tick > m_last_recv_tick + CLIENT_TIMEOUT) {
          log("client timeout, uid=%u ", GetUserId());
          forceClose();
          return;
      }
  }
  //登录超时
  if (!IsOpen()) {
      if (curr_tick > m_login_time + TIMEOUT_WATI_LOGIN_RESPONSE) {
          log("login timeout, handle=%d, uid=%u ", m_handle, GetUserId());
	  forceClose();
	  return;
      }
  }

  //当容器有erase,insert等操作时，
  //注意iterator失效的问题。
  //消息后入前出，从前开始检查，
  //只要查到第一个不超时的，后面的全不超时。
  list<msg_ack_t>::iterator it = m_send_msg_list.begin();
  for (;it != m_send_msg_list.end();) {
      msg_ack_t msg = *it;
      if (curr_tick >= msg.timestamp + TIMEOUT_WAITING_MSG_DATA_ACK) {
          log("!!!a msg missed, msg_id=%u, %u->%u ", msg.msg_id, msg.from_id, GetUserId());
          ++g_down_msg_miss_cnt;
          it = m_send_msg_list.erase(it++);  //必须使用后置
      } 
      else 
          break;
  }
}




CMsgConn::CMsgConn(const string& conn_name):m_user_id(0), m_bOpen(false), 
                                            m_bKickOff(false), m_conn_name(conn_name)
                                            m_last_seq_no(0), m_msg_cnt_per_sec(0)
                                            m_online_status(IM::BaseDefine::USER_STATUS_OFFLINE)
{
    m_send_msg_list.clear();
}


CMsgConn::~CMsgConn(){}


void init_msg_conn()
{
  g_last_stat_tick = Timestamp::now();
  signal(SIGUSR1, signal_handler_usr1); //用户自定义信号
  signal(SIGUSR2, signal_handler_usr2);
  signal(SIGHUP, signal_handler_hup);
  netlib_register_timer(msg_conn_timer_callback, NULL, 1000);
  g_pTimerLoop->runEvery(1, msg_conn_timer_callback); //1s定时
  s_file_handler = CFileHandler::getInstance();
  s_group_chat = CGroupChat::GetInstance();
}


void CMsgConn::SendPdu(CImPdu* pPdu) 
{
  m_conn->send(m_pPdu->GetBuffer(), pPdu->GetLength());
}





static void signal_handler_usr1(int sig_no)
{
  if (sig_no == SIGUSR1) {
      log("receive SIGUSR1 ");
      g_up_msg_total_cnt = 0;
      g_up_msg_miss_cnt = 0;
      g_down_msg_total_cnt = 0;
      g_down_msg_miss_cnt = 0;
  }
}


static void signal_handler_usr2(int sig_no)
{
  if (sig_no == SIGUSR2) {
      log("receive SIGUSR2 ");
      g_log_msg_toggle = !g_log_msg_toggle;
  }
}


static void signal_handler_hup(int sig_no)
{
  if (sig_no == SIGHUP) {
      log("receive SIGHUP exit... ");
      exit(0);
  }
}



void CMsgConn::SendUserStatusUpdate(uint32_t user_status)
{
  if (!m_bOpen) 
      return;
    
  CImUser* pImUser = CImUserManager::GetInstance()->GetImUserById(GetUserId());
  if (!pImUser) 
        return;
    
  // 只有上下线通知才通知LoginServer
  if (user_status == ::IM::BaseDefine::USER_STATUS_ONLINE) {
      IM::Server::IMUserCntUpdate msg;
      msg.set_user_action(USER_CNT_INC);
      msg.set_user_id(pImUser->GetUserId());
      CImPdu pdu;
      pdu.SetPBMsg(&msg);
      pdu.SetServiceId(SID_OTHER);
      pdu.SetCommandId(CID_OTHER_USER_CNT_UPDATE);
      send_to_all_login_server(&pdu);
     
      IM::Server::IMUserStatusUpdate msg2;
      msg2.set_user_status(::IM::BaseDefine::USER_STATUS_ONLINE);
      msg2.set_user_id(pImUser->GetUserId());
      msg2.set_client_type((::IM::BaseDefine::ClientType)m_client_type);
      CImPdu pdu2;
      pdu2.SetPBMsg(&msg2);
      pdu2.SetServiceId(SID_OTHER);
      pdu2.SetCommandId(CID_OTHER_USER_STATUS_UPDATE); 
      send_to_all_route_server(&pdu2);
  } 
  else if (user_status == ::IM::BaseDefine::USER_STATUS_OFFLINE) {
      IM::Server::IMUserCntUpdate msg;
      msg.set_user_action(USER_CNT_DEC);
      msg.set_user_id(pImUser->GetUserId());
      CImPdu pdu;
      pdu.SetPBMsg(&msg);
      pdu.SetServiceId(SID_OTHER);
      pdu.SetCommandId(CID_OTHER_USER_CNT_UPDATE);
      send_to_all_login_server(&pdu);
     
      IM::Server::IMUserStatusUpdate msg2;
      msg2.set_user_status(::IM::BaseDefine::USER_STATUS_OFFLINE);
      msg2.set_user_id(pImUser->GetUserId());
      msg2.set_client_type((::IM::BaseDefine::ClientType)m_client_type);
      CImPdu pdu2;
      pdu2.SetPBMsg(&msg2);
      pdu2.SetServiceId(SID_OTHER);
      pdu2.SetCommandId(CID_OTHER_USER_STATUS_UPDATE);
      send_to_all_route_server(&pdu2);
  }
}



//这是多线程安全的？
void CMsgConn::HandlePdu(CImPdu* pPdu)
{
  // request authorization check
  if (pPdu->GetCommandId() != CID_LOGIN_REQ_USERLOGIN 
      && !IsOpen() && IsKickOff()) {
      log("HandlePdu, wrong msg. ");
      throw CPduException(pPdu->GetServiceId(), pPdu->GetCommandId(), 
                          ERROR_CODE_WRONG_SERVICE_ID, "HandlePdu error, user not login. ");
      return;
  }
  switch (pPdu->GetCommandId()) {
  case CID_OTHER_HEARTBEAT:
      _HandleHeartBeat(pPdu);
      break;
  case CID_LOGIN_REQ_USERLOGIN:
      _HandleLoginRequest(pPdu );
      break;
  case CID_LOGIN_REQ_LOGINOUT:
      _HandleLoginOutRequest(pPdu);
      break;
  case CID_LOGIN_REQ_DEVICETOKEN:
      _HandleClientDeviceToken(pPdu);
      break;
  case CID_LOGIN_REQ_KICKPCCLIENT:
      _HandleKickPCClient(pPdu);
      break;
  case CID_LOGIN_REQ_PUSH_SHIELD:
      _HandlePushShieldRequest(pPdu);
      break;
    
  case CID_LOGIN_REQ_QUERY_PUSH_SHIELD:
      _HandleQueryPushShieldRequest(pPdu);
      break;
  case CID_MSG_DATA:
      _HandleClientMsgData(pPdu);
      break;
  case CID_MSG_DATA_ACK:
      _HandleClientMsgDataAck(pPdu);
      break;
  case CID_MSG_TIME_REQUEST:
      _HandleClientTimeRequest(pPdu);
      break;
  case CID_MSG_LIST_REQUEST:
      _HandleClientGetMsgListRequest(pPdu);
      break;
  case CID_MSG_GET_BY_MSG_ID_REQ:
      _HandleClientGetMsgByMsgIdRequest(pPdu);
      break;
  case CID_MSG_UNREAD_CNT_REQUEST:
      _HandleClientUnreadMsgCntRequest(pPdu );
      break;
  case CID_MSG_READ_ACK:
      _HandleClientMsgReadAck(pPdu);
      break;
  case CID_MSG_GET_LATEST_MSG_ID_REQ:
      _HandleClientGetLatestMsgIDReq(pPdu);
      break;
  case CID_SWITCH_P2P_CMD:
      _HandleClientP2PCmdMsg(pPdu );
      break;
  case CID_BUDDY_LIST_RECENT_CONTACT_SESSION_REQUEST:
      _HandleClientRecentContactSessionRequest(pPdu);
      break;
  case CID_BUDDY_LIST_USER_INFO_REQUEST:
      _HandleClientUserInfoRequest( pPdu );
      break;
  case CID_BUDDY_LIST_REMOVE_SESSION_REQ:
      _HandleClientRemoveSessionRequest( pPdu );
      break;
  case CID_BUDDY_LIST_ALL_USER_REQUEST:
      _HandleClientAllUserRequest(pPdu );
      break;
  case CID_BUDDY_LIST_CHANGE_AVATAR_REQUEST:
      _HandleChangeAvatarRequest(pPdu);
      break;
  case CID_BUDDY_LIST_CHANGE_SIGN_INFO_REQUEST:
      _HandleChangeSignInfoRequest(pPdu);
      break;
  case CID_BUDDY_LIST_USERS_STATUS_REQUEST:
      _HandleClientUsersStatusRequest(pPdu);
      break;
  case CID_BUDDY_LIST_DEPARTMENT_REQUEST:
      _HandleClientDepartmentRequest(pPdu);
      break;
  // for group process
  case CID_GROUP_NORMAL_LIST_REQUEST:
      s_group_chat->HandleClientGroupNormalRequest(pPdu, this);
      break;
  case CID_GROUP_INFO_REQUEST:
      s_group_chat->HandleClientGroupInfoRequest(pPdu, this);
      break;
  case CID_GROUP_CREATE_REQUEST:
      s_group_chat->HandleClientGroupCreateRequest(pPdu, this);
      break;
  case CID_GROUP_CHANGE_MEMBER_REQUEST:
      s_group_chat->HandleClientGroupChangeMemberRequest(pPdu, this);
      break;
  case CID_GROUP_SHIELD_GROUP_REQUEST:
      s_group_chat->HandleClientGroupShieldGroupRequest(pPdu, this);
      break;
      
  case CID_FILE_REQUEST:
      s_file_handler->HandleClientFileRequest(this, pPdu);
      break;
  case CID_FILE_HAS_OFFLINE_REQ:
      s_file_handler->HandleClientFileHasOfflineReq(this, pPdu);
      break;
  case CID_FILE_ADD_OFFLINE_REQ:
      s_file_handler->HandleClientFileAddOfflineReq(this, pPdu);
      break;
  case CID_FILE_DEL_OFFLINE_REQ:
      s_file_handler->HandleClientFileDelOfflineReq(this, pPdu);
      break;
  default:
      log("wrong msg, cmd id=%d, user id=%u. ", pPdu->GetCommandId(), GetUserId());
           break;
  }
}


void CMsgConn::_HandleHeartBeat(CImPdu *pPdu)
{
  //响应
  SendPdu(pPdu);
}


// process: send validate request to db server
void CMsgConn::_HandleLoginRequest(CImPdu* pPdu)
{
  // refuse second validate request
  if (m_login_name.length() != 0) {
      log("duplicate LoginRequest in the same conn ");
      return;
  }

  // check if all server connection are OK
  uint32_t result = 0;
  string result_string = "";
  //专用于登录认证的db_server连接
   TcpClientInfo * pDbClient = get_db_serv_client_for_login();
   if (!pDbConn) {
       result = IM::BaseDefine::REFUSE_REASON_NO_DB_SERVER;
       result_string = "服务端异常";
   }
   else if (!is_login_server_available()) {
       result = IM::BaseDefine::REFUSE_REASON_NO_LOGIN_SERVER;
      result_string = "服务端异常";
  }
  else if (!is_route_server_available()) {
      result = IM::BaseDefine::REFUSE_REASON_NO_ROUTE_SERVER;
      result_string = "服务端异常";   
  }
  if (result) {
      IM::Login::IMLoginRes msg;
      msg.set_server_time(time(NULL));
      msg.set_result_code((IM::BaseDefine::ResultType)result);
      msg.set_result_string(result_string);
      CImPdu pdu;
      pdu.SetPBMsg(&msg);
      pdu.SetServiceId(SID_LOGIN);
      pdu.SetCommandId(CID_LOGIN_RES_USERLOGIN);
      pdu.SetSeqNum(pPdu->GetSeqNum());
      SendPdu(&pdu);
      forceClose();
      return;
  }
  IM::Login::IMLoginReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
 //假如是汉字，则转成拼音
  m_login_name = msg.user_name();
  string password = msg.password();
  uint32_t online_status = msg.online_status();
  if (online_status < IM::BaseDefine::USER_STATUS_ONLINE 
      || online_status > IM::BaseDefine::USER_STATUS_LEAVE) {
      log("HandleLoginReq, online status wrong: %u ", online_status);
      online_status = IM::BaseDefine::USER_STATUS_ONLINE;
  }
  m_client_version = msg.client_version();
  m_client_type = msg.client_type();
  m_online_status = online_status;
  log("HandleLoginReq, user_name=%s, status=%u, client_type=%u, client=%s, ",
       m_login_name.c_str(), online_status, m_client_type, m_client_version.c_str());
  CImUser* pImUser = CImUserManager::GetInstance()->GetImUserByLoginName(GetLoginName());
  if (!pImUser) {
      pImUser = new CImUser(GetLoginName());
      CImUserManager::GetInstance()->AddImUserByLoginName(GetLoginName(), pImUser);
  }
  pImUser->AddUnValidateMsgConn(this);//还未被验证的连接
    
  CDbAttachData attach_data(ATTACH_TYPE_HANDLE, m_handle, 0);
  // continue to validate if the user is OK
  IM::Server::IMValidateReq msg2;
  msg2.set_user_name(msg.user_name());
  msg2.set_password(password);
  msg2.set_attach_data(attach_data.GetBuffer(), attach_data.GetLength());
  CImPdu pdu;
  pdu.SetPBMsg(&msg2);
  pdu.SetServiceId(SID_OTHER);
  pdu.SetCommandId(CID_OTHER_VALIDATE_REQ);
  pdu.SetSeqNum(pPdu->GetSeqNum());
  //通过dbClient向dbServer发送数据。
  pDbClient->m_client->connection->send(pPdu->GetBuffer(), 
                                        pPdu->GetLength());
}


//@1.发送给db退出信息，@2.发送给请求用户的回复
void CMsgConn::_HandleLoginOutRequest(CImPdu *pPdu)
{
  log("HandleLoginOutRequest, user_id=%d, client_type=%u. ", 
       GetUserId(), GetClientType());
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
      IM::Login::IMDeviceTokenReq msg;
      msg.set_user_id(GetUserId());
      msg.set_device_token("");
      CImPdu pdu;
      pdu.SetPBMsg(&msg);
      pdu.SetServiceId(SID_LOGIN);
      pdu.SetCommandId(CID_LOGIN_REQ_DEVICETOKEN);
      pdu.SetSeqNum(pPdu->GetSeqNum());
      pDbClient->m_client->connection->send(pPdu->GetBuffer(),
                                            pPdu->GetLength());
  }
  
  IM::Login::IMLogoutRsp msg2;
  msg2.set_result_code(0);
  CImPdu pdu2;
  pdu2.SetPBMsg(&msg2);
  pdu2.SetServiceId(SID_LOGIN);
  pdu2.SetCommandId(CID_LOGIN_RES_LOGINOUT);
  pdu2.SetSeqNum(pPdu->GetSeqNum());
  SendPdu(&pdu2);
  forceClose();
}


void CMsgConn::_HandleKickPCClient(CImPdu *pPdu)
{
  IM::Login::IMKickPCClientReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t user_id = GetUserId();
  if (!CHECK_CLIENT_TYPE_MOBILE(GetClientType())){
      log("HandleKickPCClient, user_id = %u, cmd must come from mobile client. ", user_id);
      return;
  }
  log("HandleKickPCClient, user_id = %u. ", user_id);
  
  CImUser* pImUser = CImUserManager::GetInstance()->GetImUserById(user_id);
  if (pImUser)
      pImUser->KickOutSameClientType(CLIENT_TYPE_MAC, 
                                     IM::BaseDefine::KICK_REASON_MOBILE_KICK,this);
  TcpClientInfo* pRouteClient = get_route_serv_client(); 
  if (pRouteClient) {
     IM::Server::IMServerKickUser msg2;
     msg2.set_user_id(user_id);
     msg2.set_client_type(::IM::BaseDefine::CLIENT_TYPE_MAC);
     msg2.set_reason(IM::BaseDefine::KICK_REASON_MOBILE_KICK);
     CImPdu pdu;
     pdu.SetPBMsg(&msg2);
     pdu.SetServiceId(SID_OTHER);
     pdu.SetCommandId(CID_OTHER_SERVER_KICK_USER);
     pRouteClient->m_client->connection->send(pPdu->GetBuffer(),
                                            pPdu->GetLength());
  }
    
    IM::Login::IMKickPCClientRsp msg2;
    msg2.set_user_id(user_id);
    msg2.set_result_code(0);
    CImPdu pdu;
    pdu.SetPBMsg(&msg2);
    pdu.SetServiceId(SID_LOGIN);
    pdu.SetCommandId(CID_LOGIN_RES_KICKPCCLIENT);
    pdu.SetSeqNum(pPdu->GetSeqNum());
    SendPdu(&pdu);
}


// 请求最近联系会话列表
MsgConn::_HandleClientRecentContactSessionRequest(CImPdu *pPdu)
{
  TcpClientInfo* pDbClient = get_db_serv_client_for_login();
  if (!pDbClient) 
      return;
  
  IM::Buddy::IMRecentContactSessionReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  log("HandleClientRecentContactSessionRequest, user_id=%u, latest_update_time=%u. ", 
       GetUserId(), msg.latest_update_time());

  msg.set_user_id(GetUserId());
  CDbAttachData attach_data(ATTACH_TYPE_HANDLE, m_handle, 0);
  msg.set_attach_data(attach_data.GetBuffer(), attach_data.GetLength());
  pPdu->SetPBMsg(&msg);
  pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                          pPdu->GetLength());
}


MsgConn::_HandleClientMsgData(CImPdu* pPdu)
{
  IM::Message::IMMsgData msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  if (msg.msg_data().length() == 0) {
      log("discard an empty message, uid=%u ", GetUserId());
      return;
  }

  if (m_msg_cnt_per_sec >= MAX_MSG_CNT_PER_SECOND) {
      log("!!!too much msg cnt in one second, uid=%u ", GetUserId());
      return;
  }
  
  if (msg.from_user_id() == msg.to_session_id() 
      && CHECK_MSG_TYPE_SINGLE(msg.msg_type())){
      log("!!!from_user_id == to_user_id. ");
      return;
  }

  m_msg_cnt_per_sec++;

  uint32_t to_session_id = msg.to_session_id();
  uint32_t msg_id = msg.msg_id();
  uint8_t msg_type = msg.msg_type();
  string msg_data = msg.msg_data();
  if (g_log_msg_toggle) 
      log("HandleClientMsgData, %d->%d, msg_type=%u, msg_id=%u. ", 
           GetUserId(), to_session_id, msg_type, msg_id);

  uint32_t cur_time = time(NULL);
  CDbAttachData attach_data(ATTACH_TYPE_HANDLE, m_handle, 0);
  msg.set_from_user_id(GetUserId());
  msg.set_create_time(cur_time);
  msg.set_attach_data(attach_data.GetBuffer(), attach_data.GetLength());
  pPdu->SetPBMsg(&msg);
  // send to DB storage server
  TcpClientInfo* pDbClient = get_db_serv_client();
  if (pDbClient) 
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
}

//??
void CMsgConn::_HandleClientMsgDataAck(CImPdu* pPdu)
{
  IM::Message::IMMsgDataAck msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  
  IM::BaseDefine::SessionType session_type = msg.session_type();
  if (session_type == IM::BaseDefine::SESSION_TYPE_SINGLE){
      uint32_t msg_id = msg.msg_id();
      uint32_t session_id = msg.session_id();
      DelFromSendList(msg_id, session_id);
  }
}



void CMsgConn::_HandleClientTimeRequest(CImPdu* pPdu)
{
  IM::Message::IMClientTimeRsp msg;
  msg.set_server_time((uint32_t)time(NULL));
  CImPdu pdu;
  pdu.SetPBMsg(&msg);
  pdu.SetServiceId(SID_MSG);
  pdu.SetCommandId(CID_MSG_TIME_RESPONSE);
  pdu.SetSeqNum(pPdu->GetSeqNum());
  SendPdu(&pdu);
}


//获取消息列表
MsgConn::_HandleClientGetMsgListRequest(CImPdu *pPdu)
{
  IM::Message::IMGetMsgListReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t session_id = msg.session_id();
  uint32_t msg_id_begin = msg.msg_id_begin();
  uint32_t msg_cnt = msg.msg_cnt();
  uint32_t session_type = msg.session_type();
  log("HandleClientGetMsgListRequest, req_id=%u, 
       session_type=%u, session_id=%u, msg_id_begin=%u, msg_cnt=%u. ",
       GetUserId(), session_type, session_id, msg_id_begin, msg_cnt);
  TcpClientInfo* pDBClient = get_db_serv_client_for_login();
  if (pDBClient) {
      CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
      msg.set_user_id(GetUserId());
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}



void CMsgConn::_HandleClientGetMsgByMsgIdRequest(CImPdu *pPdu)
{
  IM::Message::IMGetMsgByIdReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t session_id = msg.session_id();
  uint32_t session_type = msg.session_type();
  uint32_t msg_cnt = msg.msg_id_list_size();
  log("_HandleClientGetMsgByMsgIdRequest, req_id=%u, 
       session_type=%u, session_id=%u, msg_cnt=%u.",
       GetUserId(), session_type, session_id, msg_cnt);
  TcpClientInfo* pDBClient = get_db_serv_client_for_login();
  if (pDBClient) {
      CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
      msg.set_user_id(GetUserId());
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}


//获取未读信息请求
MsgConn::_HandleClientUnreadMsgCntRequest(CImPdu* pPdu)
{
  log("HandleClientUnreadMsgCntReq, from_id=%u ", GetUserId());
  IM::Message::IMUnreadMsgCntReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  
  TcpClientInfo* pDBClient = get_db_serv_client_for_login();
  if (pDBConn) {
  	CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
        msg.set_user_id(GetUserId());
        msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
        pPdu->SetPBMsg(&msg);
        pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                                pPdu->GetLength());
  }
}


//对client读取信息的确认？？？
MsgConn::_HandleClientMsgReadAck(CImPdu* pPdu)
{
  IM::Message::IMMsgDataReadAck msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t session_type = msg.session_type();
  uint32_t session_id = msg.session_id();
  uint32_t msg_id = msg.msg_id();
  log("HandleClientMsgReadAck, user_id=%u, session_id=%u, 
       msg_id=%u, session_type=%u. ", GetUserId(),session_id, msg_id, session_type);
  
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
      msg.set_user_id(GetUserId());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
  IM::Message::IMMsgDataReadNotify msg2;
  msg2.set_user_id(GetUserId());
  msg2.set_session_id(session_id);
  msg2.set_msg_id(msg_id);
  msg2.set_session_type((IM::BaseDefine::SessionType)session_type);
  CImPdu pdu;
  pdu.SetPBMsg(&msg2);
  pdu.SetServiceId(SID_MSG);
  pdu.SetCommandId(CID_MSG_READ_NOTIFY);
  CImUser* pUser = CImUserManager::GetInstance()->GetImUserById(GetUserId());
  if (pUser)
      pUser->BroadcastPdu(&pdu, this);
  TcpClientInfo* pRouteClient = get_route_serv_client();
  if (pRouteClient) {
      pRouteClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
  
  if (session_type == IM::BaseDefine::SESSION_TYPE_SINGLE)
      DelFromSendList(msg_id, session_id);
}



//获取用户信息
void CMsgConn::_HandleClientUserInfoRequest(CImPdu* pPdu)
{
  IM::Buddy::IMUsersInfoReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t user_cnt = msg.user_id_list_size();
  log("HandleClientUserInfoReq, req_id=%u, user_cnt=%u ", GetUserId(), user_cnt);
  TcpClientInfo* pDBClient = get_db_serv_client_for_login();
  if (pDBClient) {
      CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
      msg.set_user_id(GetUserId());
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}



MsgConn::_HandleClientRemoveSessionRequest(CImPdu* pPdu)
{
  IM::Buddy::IMRemoveSessionReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t session_type = msg.session_type();
  uint32_t session_id = msg.session_id();
  log("HandleClientRemoveSessionReq, user_id=%u, 
       session_id=%u, type=%u ", GetUserId(), session_id, session_type);
 
  TcpClientInfo* pDBClient = get_db_serv_client(); 
  if (pDBClient) {
      CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
      msg.set_user_id(GetUserId());
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
  
  if (session_type == IM::BaseDefine::SESSION_TYPE_SINGLE){
      IM::Buddy::IMRemoveSessionNotify msg2;
      msg2.set_user_id(GetUserId());
      msg2.set_session_id(session_id);
      msg2.set_session_type((IM::BaseDefine::SessionType)session_type);
      CImPdu pdu;
      pdu.SetPBMsg(&msg2);
      pdu.SetServiceId(SID_BUDDY_LIST);
      pdu.SetCommandId(CID_BUDDY_LIST_REMOVE_SESSION_NOTIFY);
      CImUser* pImUser = CImUserManager::GetInstance()->GetImUserById(GetUserId());
      if (pImUser) 
          pImUser->BroadcastPdu(&pdu, this);
      TcpClientInfo* pRouteClient = get_route_serv_client();
      if (pRouteClient) 
          pRouteClient->m_client->connection()->send(pPdu->GetBuffer(),
                                                     pPdu->GetLength());
  }
}


//???
MsgConn::_HandleClientAllUserRequest(CImPdu* pPdu)
{
  IM::Buddy::IMAllUserReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t latest_update_time = msg.latest_update_time();
  log("HandleClientAllUserReq, user_id=%u, 
       latest_update_time=%u. ", GetUserId(), latest_update_time);
  
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
      CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
      msg.set_user_id(GetUserId());
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}



void CMsgConn::_HandleChangeAvatarRequest(CImPdu* pPdu)
{
  IM::Buddy::IMChangeAvatarReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  log("HandleChangeAvatarRequest, user_id=%u ", GetUserId());
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
      msg.set_user_id(GetUserId());
      pPdu->SetPBMsg(&msg);
      pDbClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}



MsgConn::_HandleClientUsersStatusRequest(CImPdu* pPdu)
{
  IM::Buddy::IMUsersStatReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  uint32_t user_count = msg.user_id_list_size();
  log("HandleClientUsersStatusReq, user_id=%u, query_count=%u.", GetUserId(), user_count);
  
  TcpClientInfo* pRouteClient = get_route_serv_client();
  if(pRouteClient){
      msg.set_user_id(GetUserId());
      CPduAttachData attach(ATTACH_TYPE_HANDLE, m_handle,0, NULL);
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      pPdu->SetPBMsg(&msg);
      pRouteClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}


void CMsgConn::_HandleClientDepartmentRequest(CImPdu *pPdu)
{
    IM::Buddy::IMDepartmentReq msg;
    CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
    log("HandleClientDepartmentRequest, user_id=%u, 
         latest_update_time=%u.", GetUserId(), msg.latest_update_time());
    TcpClientInfo* pDBClient = get_db_serv_client();
    if (pDBClient) {
        CDbAttachData attach(ATTACH_TYPE_HANDLE, m_handle, 0);
        msg.set_user_id(GetUserId());
        msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
        pPdu->SetPBMsg(&msg);
        pDBClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
    }
}



void CMsgConn::_HandleClientDeviceToken(CImPdu *pPdu)
{
  if (!CHECK_CLIENT_TYPE_MOBILE(GetClientType())){
      log("HandleClientDeviceToken, user_id=%u, 
           not mobile client.", GetUserId());
      return;
  }
  IM::Login::IMDeviceTokenReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  string device_token = msg.device_token();
  log("HandleClientDeviceToken, user_id=%u, 
       device_token=%s ", GetUserId(), device_token.c_str());
  
  IM::Login::IMDeviceTokenRsp msg2;
  msg.set_user_id(GetUserId());
  msg.set_client_type((::IM::BaseDefine::ClientType)GetClientType());
  CImPdu pdu;
  pdu.SetPBMsg(&msg2);
  pdu.SetServiceId(SID_LOGIN);
  pdu.SetCommandId(CID_LOGIN_RES_DEVICETOKEN);
  pdu.SetSeqNum(pPdu->GetSeqNum());
  SendPdu(&pdu);
  
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
      msg.set_user_id(GetUserId());
      pPdu->SetPBMsg(&msg);
      pDBClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}

//发送消息队列
MsgConn::AddToSendList(uint32_t msg_id, uint32_t from_id)
{
  //log("AddSendMsg, seq_no=%u, from_id=%u ", seq_no, from_id);
  msg_ack_t msg;
  msg.msg_id = msg_id;
  msg.from_id = from_id;
  msg.timestamp = get_tick_count();
  m_send_msg_list.push_back(msg);

  g_down_msg_total_cnt++;
}


MsgConn::DelFromSendList(uint32_t msg_id, uint32_t from_id)
{
  //log("DelSendMsg, seq_no=%u, from_id=%u ", seq_no, from_id);
  for (list<msg_ack_t>::iterator it = m_send_msg_list.begin(); 
       it != m_send_msg_list.end(); it++) {
      msg_ack_t msg = *it;
      if ( (msg.msg_id == msg_id) 
            && (msg.from_id == from_id) ) {
          m_send_msg_list.erase(it);
	  break;
      }
  }
}


uint32_t CMsgConn::GetClientTypeFlag()
{
  uint32_t client_type_flag = 0x00;
  if (CHECK_CLIENT_TYPE_PC(GetClientType()))
      client_type_flag = CLIENT_TYPE_FLAG_PC;
  else if (CHECK_CLIENT_TYPE_MOBILE(GetClientType()))
      client_type_flag = CLIENT_TYPE_FLAG_MOBILE;
  return client_type_flag;
}


void CMsgConn::_HandleChangeSignInfoRequest(CImPdu* pPdu) 
{
  IM::Buddy::IMChangeSignInfoReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));
  log("HandleChangeSignInfoRequest, user_id=%u ", GetUserId());
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
       msg.set_user_id(GetUserId());
       CPduAttachData attach(ATTACH_TYPE_HANDLE, m_handle,0, NULL);
       msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
  
       pPdu->SetPBMsg(&msg);
       pDBClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}



void CMsgConn::_HandlePushShieldRequest(CImPdu* pPdu)
{
  IM::Login::IMPushShieldReq msg;
  CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), 
                     pPdu->GetBodyLength()));
  log("_HandlePushShieldRequest, user_id=%u, 
       shield_status ", GetUserId(), msg.shield_status());
  TcpClientInfo* pDBClient = get_db_serv_client();
  if (pDBClient) {
      msg.set_user_id(GetUserId());
      CPduAttachData attach(ATTACH_TYPE_HANDLE, m_handle,0, NULL);
      msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
      
      pPdu->SetPBMsg(&msg);
      pDBClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}



void CMsgConn::_HandleQueryPushShieldRequest(CImPdu* pPdu)
{
    IM::Login::IMQueryPushShieldReq msg;
    CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), 
                       pPdu->GetBodyLength()));
    log("HandleChangeSignInfoRequest, user_id=%u ", GetUserId());
    CDBClient* pDBClient = get_db_serv_client();
    if (pDBClient) {
        msg.set_user_id(GetUserId());
        CPduAttachData attach(ATTACH_TYPE_HANDLE, m_handle,0, NULL);
        msg.set_attach_data(attach.GetBuffer(), attach.GetLength());
        
        pPdu->SetPBMsg(&msg);
        pDBClient->m_client->connection()->send(pPdu->GetBuffer(),
                                              pPdu->GetLength());
  }
}


