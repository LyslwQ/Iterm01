#include "MessageContent.h"
#include "../CachePool.h"
#include "../DBPool.h"

#include "../model/MessageModel.h"
#include "../model/GroupMessageModel.h"
#include "Common.h"
#include "../model/GroupModel.h"
#include "../../base/ImPduBase.h"
#include "../../base/pb/protocol/IM.Message.pb.h"
#include "../model/SessionModel.h"
#include "../model/RelationModel.h"


namespace DB_PROXY {
//@1.判断session类型。
//@2.对于单人聊天的，先验证两者的关系是否正常。再用related获得所需的msg。
//@3.对于群聊的，先验证是否是群成员，再用groupId去获取msg。
void getMessage(CImPdu* pPdu, const TcpConnectionPtr& conn)
{
  IM::Message::IMGetMsgListReq msg;
  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      //对于getMessage的请求，用户其实只需要传来的数据有：
      //@1.session_id   @2.msg_cnt
      uint32_t nUserId = msg.user_id();
      uint32_t nPeerId = msg.session_id();
      uint32_t nMsgId = msg.msg_id_begin();
      uint32_t nMsgCnt = msg.msg_cnt();     //拉取的消息数目
      IM::BaseDefine::SessionType nSessionType = msg.session_type();
      if (IM::BaseDefine::SessionType_IsValid(nSessionType)){  
          CImPdu* pPduResp = new CImPdu;
          IM::Message::IMGetMsgListRsp msgResp;

          list<IM::BaseDefine::MsgInfo> lsMsg;

          if (nSessionType == IM::BaseDefine::SESSION_TYPE_SINGLE){//获取单个用户会话信息
              CMessageModel::getInstance()->getMessage(nUserId, nPeerId, nMsgId, nMsgCnt, lsMsg);
          }
          else if (nSessionType == IM::BaseDefine::SESSION_TYPE_GROUP){//获取群聊消息
              if (CGroupModel::getInstance()->isInGroup(nUserId, nPeerId)){ //先判断是否是群成员,group和成员的关系是存放在redis中
	          CGroupMessageModel::getInstance()->getMessage(nUserId, nPeerId, nMsgId, nMsgCnt, lsMsg);
	      }
          }

          msgResp.set_user_id(nUserId);
          msgResp.set_session_id(nPeerId);
          msgResp.set_msg_id_begin(nMsgId);
          msgResp.set_session_type(nSessionType);
          for (auto it = lsMsg.begin(); it != lsMsg.end(); ++it){
              IM::BaseDefine::MsgInfo* pMsg = msgResp.add_msg_list();
	      //            *pMsg = *it;
	      pMsg->set_msg_id(it->msg_id());
	      pMsg->set_from_session_id(it->from_session_id());
	      pMsg->set_create_time(it->create_time());
	      pMsg->set_msg_type(it->msg_type());
	      pMsg->set_msg_data(it->msg_data());
	      log("userId=%u, peerId=%u, msgId=%u", nUserId, nPeerId, it->msg_id());
          } 

          log("userId=%u, peerId=%u, msgId=%u, msgCnt=%u, count=%u", 
          nUserId, nPeerId, nMsgId, nMsgCnt, msgResp.msg_list_size());
          msgResp.set_attach_data(msg.attach_data());
          pPduResp->SetPBMsg(&msgResp);
          pPduResp->SetSeqNum(pPdu->GetSeqNum());
          pPduResp->SetServiceId(IM::BaseDefine::SID_MSG);
          pPduResp->SetCommandId(IM::BaseDefine::CID_MSG_LIST_RESPONSE);
          conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //数据最终会在conn.Buddy所在的io线程中发送出去。
      }
     else{
         log("invalid sessionType. userId=%u, peerId=%u, msgId=%u, msgCnt=%u, sessionType=%u",
         nUserId, nPeerId, nMsgId, nMsgCnt, nSessionType);
    }
  }
  else
      log("parse pb failed");
}

//@1.判断msg的类型
//@2.对于groupMessage，应该先进行群id，群成员有效验证。
//@3.更新相应的session。
//@4.将message写进数据库，同时，更新redis缓存中的未读信息。
void sendMessage(CImPdu* pPdu, const TcpConnectionPtr& conn)
{
  IM::Message::IMMsgData msg;
  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      uint32_t nFromId = msg.from_user_id();
      uint32_t nToId = msg.to_session_id();
      uint32_t nCreateTime = msg.create_time();
      IM::BaseDefine::MsgType nMsgType = msg.msg_type();
      uint32_t nMsgLen = msg.msg_data().length();

      uint32_t nNow = (uint32_t)time(NULL);
      if (IM::BaseDefine::MsgType_IsValid(nMsgType)){
          if (nMsgLen != 0){
          CImPdu* pPduResp = new CImPdu;

          uint32_t nMsgId = INVALID_VALUE;
          uint32_t nSessionId = INVALID_VALUE;
          uint32_t nPeerSessionId = INVALID_VALUE;

	  CMessageModel* pMsgModel = CMessageModel::getInstance();
	  CGroupMessageModel* pGroupMsgModel = CGroupMessageModel::getInstance();
	  if (nMsgType == IM::BaseDefine::MSG_TYPE_GROUP_TEXT) { //群聊
	      CGroupModel* pGroupModel = CGroupModel::getInstance();
              //@1.群是否存在？ @2.是否是群成员？
              if (pGroupModel->isValidateGroupId(nToId) && pGroupModel->isInGroup(nFromId, nToId)){
	          nSessionId = CSessionModel::getInstance()->getSessionId(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_GROUP, false);
	          if (INVALID_VALUE == nSessionId) {
	              nSessionId = CSessionModel::getInstance()->addSession(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_GROUP);
	          }   
                  if (nSessionId != INVALID_VALUE){
                      nMsgId = pGroupMsgModel->getMsgId(nToId);
	              if (nMsgId != INVALID_VALUE) {
	                  pGroupMsgModel->sendMessage(nFromId, nToId, nMsgType, nCreateTime, nMsgId, (string&)msg.msg_data());
	                  CSessionModel::getInstance()->updateSession(nSessionId, nNow);
	              }  
	          }
              }
              else{
                  log("invalid groupId. fromId=%u, groupId=%u", nFromId, nToId);
	          delete pPduResp; 
                  return;
              }
          }
          else if (nMsgType == IM::BaseDefine::MSG_TYPE_GROUP_AUDIO) {
              CGroupModel* pGroupModel = CGroupModel::getInstance();
	      if (pGroupModel->isValidateGroupId(nToId) && pGroupModel->isInGroup(nFromId, nToId)){
	          nSessionId = CSessionModel::getInstance()->getSessionId(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_GROUP, false); 
                  if (INVALID_VALUE == nSessionId) { 
                      nSessionId = CSessionModel::getInstance()->addSession(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_GROUP);
	           }   
                   if (nSessionId != INVALID_VALUE){
	               nMsgId = pGroupMsgModel->getMsgId(nToId);
	               if (nMsgId != INVALID_VALUE){
	                   pGroupMsgModel->sendAudioMessage(nFromId, nToId, nMsgType, nCreateTime, nMsgId, msg.msg_data().c_str(), nMsgLen);
	                   CSessionModel::getInstance()->updateSession(nSessionId, nNow);
	               }  
                   }
	       }
               else{
	           log("invalid groupId. fromId=%u, groupId=%u", nFromId, nToId);
	           delete pPduResp;
	           return;
               }
           }
           else if (nMsgType == IM::BaseDefine::MSG_TYPE_SINGLE_TEXT) {
               if (nFromId != nToId) {
	           nSessionId = CSessionModel::getInstance()->getSessionId(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_SINGLE, false);
	           if (INVALID_VALUE == nSessionId) 
	               nSessionId = CSessionModel::getInstance()->addSession(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_SINGLE);
	           nPeerSessionId = CSessionModel::getInstance()->getSessionId(nToId, nFromId, IM::BaseDefine::SESSION_TYPE_SINGLE, false);
	           if (INVALID_VALUE == nPeerSessionId)
	               nSessionId = CSessionModel::getInstance()->addSession(nToId, nFromId, IM::BaseDefine::SESSION_TYPE_SINGLE);  
                       //不是应该先先验证两者的related，再执行上面的三个if吗？？？  是不加好友也可以发信息的情况？？
	               uint32_t nRelateId = CRelationModel::getInstance()->getRelationId(nFromId, nToId, true);
                      if (nSessionId != INVALID_VALUE && nRelateId != INVALID_VALUE){
	                  nMsgId = pMsgModel->getMsgId(nRelateId);
	                  if (nMsgId != INVALID_VALUE){
                              pMsgModel->sendMessage(nRelateId, nFromId, nToId, nMsgType, nCreateTime, nMsgId, (string&)msg.msg_data());
	                      CSessionModel::getInstance()->updateSession(nSessionId, nNow);
	                      CSessionModel::getInstance()->updateSession(nPeerSessionId, nNow);
	                  }
                          else{
	                      log("msgId is invalid. fromId=%u, toId=%u, nRelateId=%u, nSessionId=%u, nMsgType=%u", 
                                   nFromId, nToId, nRelateId, nSessionId, nMsgType);
                         }
                     }
	             else {
	                log("sessionId or relateId is invalid. fromId=%u, toId=%u, nRelateId=%u, nSessionId=%u, nMsgType=%u", 
                             nFromId, nToId, nRelateId, nSessionId, nMsgType);
	            } 
	      }
              else{
	          log("send msg to self. fromId=%u, toId=%u, msgType=%u", nFromId, nToId, nMsgType);
              }
          }
          else if (nMsgType == IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO) {
              if (nFromId != nToId){
	          nSessionId = CSessionModel::getInstance()->getSessionId(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_SINGLE, false);
	          if (INVALID_VALUE == nSessionId) {
	              nSessionId = CSessionModel::getInstance()->addSession(nFromId, nToId, IM::BaseDefine::SESSION_TYPE_SINGLE);
                  }
                  nPeerSessionId = CSessionModel::getInstance()->getSessionId(nToId, nFromId, IM::BaseDefine::SESSION_TYPE_SINGLE, false);
	          if (INVALID_VALUE == nPeerSessionId){
	              nSessionId = CSessionModel::getInstance()->addSession(nToId, nFromId, IM::BaseDefine::SESSION_TYPE_SINGLE);
	          }
	          uint32_t nRelateId = CRelationModel::getInstance()->getRelationId(nFromId, nToId, true);
	          if (nSessionId != INVALID_VALUE && nRelateId != INVALID_VALUE){
	              nMsgId = pMsgModel->getMsgId(nRelateId);
	              if (nMsgId != INVALID_VALUE) {
	                  pMsgModel->sendAudioMessage(nRelateId, nFromId, nToId, nMsgType, nCreateTime, nMsgId, msg.msg_data().c_str(), nMsgLen);
	                  CSessionModel::getInstance()->updateSession(nSessionId, nNow);
	                  CSessionModel::getInstance()->updateSession(nPeerSessionId, nNow);
	              }
	              else {
	                  log("msgId is invalid. fromId=%u, toId=%u, nRelateId=%u, nSessionId=%u, nMsgType=%u", 
                          nFromId, nToId, nRelateId, nSessionId, nMsgType);
                      }
	          }
                  else {
	              log("sessionId or relateId is invalid. fromId=%u, toId=%u, nRelateId=%u, nSessionId=%u, nMsgType=%u", 
                      nFromId, nToId, nRelateId, nSessionId, nMsgType);
	          }
              }
	      else{
	          log("send msg to self. fromId=%u, toId=%u, msgType=%u", 
                  nFromId, nToId, nMsgType);
  	      }
          }  
          log("fromId=%u, toId=%u, type=%u, msgId=%u, sessionId=%u", 
              nFromId, nToId, nMsgType, nMsgId, nSessionId);
          msg.set_msg_id(nMsgId);
          pPduResp->SetPBMsg(&msg);
          pPduResp->SetSeqNum(pPdu->GetSeqNum());
          pPduResp->SetServiceId(IM::BaseDefine::SID_MSG);
          pPduResp->SetCommandId(IM::BaseDefine::CID_MSG_DATA);
          conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //数据最终会在conn所在的io线程中发送出去。
          }
          else{
              log("msgLen error. fromId=%u, toId=%u, msgType=%u", 
              nFromId, nToId, nMsgType);
          }  
      }
      else{
          log("invalid msgType.fromId=%u, toId=%u, msgType=%u", 
               nFromId, nToId, nMsgType);
      }
   }
   else{
      log("parse pb failed");
   }
}


void getMessageById(CImPdu* pPdu, const TcpConnectionPtr& conn)
{
  IM::Message::IMGetMsgByIdReq msg; 
  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      uint32_t nUserId = msg.user_id();
      IM::BaseDefine::SessionType nType = msg.session_type();
      uint32_t nPeerId = msg.session_id();
      list<uint32_t> lsMsgId;
      uint32_t nCnt = msg.msg_id_list_size();
      for (uint32_t i = 0; i<nCnt; ++i){
          lsMsgId.push_back(msg.msg_id_list(i));
      }
      if (IM::BaseDefine::SessionType_IsValid(nType)){
          CImPdu* pPduResp = new CImPdu;
          IM::Message::IMGetMsgByIdRsp msgResp;

	  list<IM::BaseDefine::MsgInfo> lsMsg;
	  if (IM::BaseDefine::SESSION_TYPE_SINGLE == nType){
	      CMessageModel::getInstance()->getMsgByMsgId(nUserId, nPeerId, lsMsgId, lsMsg);
	  }
	  else if (IM::BaseDefine::SESSION_TYPE_GROUP){
	      CGroupMessageModel::getInstance()->getMsgByMsgId(nUserId, nPeerId, lsMsgId, lsMsg);
	  }
	  msgResp.set_user_id(nUserId);
	  msgResp.set_session_id(nPeerId);
          msgResp.set_session_type(nType);
	  for (auto it = lsMsg.begin(); it != lsMsg.end(); ++it){
              IM::BaseDefine::MsgInfo* pMsg = msgResp.add_msg_list();
	      pMsg->set_msg_id(it->msg_id());
	      pMsg->set_from_session_id(it->from_session_id());
	      pMsg->set_create_time(it->create_time());
	      pMsg->set_msg_type(it->msg_type());
	      pMsg->set_msg_data(it->msg_data());
	  }
          log("userId=%u, peerId=%u, sessionType=%u, reqMsgCnt=%u, resMsgCnt=%u", 
               nUserId, nPeerId, nType, msg.msg_id_list_size(), msgResp.msg_list_size());
          msgResp.set_attach_data(msg.attach_data());
	  pPduResp->SetPBMsg(&msgResp);
	  pPduResp->SetSeqNum(pPdu->GetSeqNum());
	  pPduResp->SetServiceId(IM::BaseDefine::SID_MSG);
	  pPduResp->SetCommandId(IM::BaseDefine::CID_MSG_GET_BY_MSG_ID_RES);
	  conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //数据最终会在conn.Buddy所在的io线程中发送出去。
      }
      else{
          log("invalid sessionType. fromId=%u, toId=%u, sessionType=%u, msgCnt=%u", 
               nUserId, nPeerId, nType, nCnt);
      }
  }
  else{
      log("parse pb failed");
  }
}


void getLatestMsgId(CImPdu* pPdu, const TcpConnectionPtr& conn)
{
  IM::Message::IMGetLatestMsgIdReq msg;
  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      uint32_t nUserId = msg.user_id();
      IM::BaseDefine::SessionType nType = msg.session_type();
      uint32_t nPeerId = msg.session_id();
      if (IM::BaseDefine::SessionType_IsValid(nType)) {
          CImPdu* pPduResp = new CImPdu;
	  IM::Message::IMGetLatestMsgIdRsp msgResp;
	  msgResp.set_user_id(nUserId);
	  msgResp.set_session_type(nType);
	  msgResp.set_session_id(nPeerId);
	  uint32_t nMsgId = INVALID_VALUE;
	  if (IM::BaseDefine::SESSION_TYPE_SINGLE == nType){
	      string strMsg;
	      IM::BaseDefine::MsgType nMsgType;
	      CMessageModel::getInstance()->getLastMsg(nUserId, nPeerId, nMsgId, strMsg, nMsgType, 1);
	  }
	  else{
	      string strMsg;
	      IM::BaseDefine::MsgType nMsgType;
	      uint32_t nFromId = INVALID_VALUE;
	      CGroupMessageModel::getInstance()->getLastMsg(nPeerId, nMsgId, strMsg, nMsgType, nFromId);
          }
	  msgResp.set_latest_msg_id(nMsgId);
          log("userId=%u, peerId=%u, sessionType=%u, msgId=%u", nUserId, nPeerId, nType, nMsgId);
	  msgResp.set_attach_data(msg.attach_data());
	  pPduResp->SetPBMsg(&msgResp);
	  pPduResp->SetSeqNum(pPdu->GetSeqNum());
	  pPduResp->SetServiceId(IM::BaseDefine::SID_MSG);
	  pPduResp->SetCommandId(IM::BaseDefine::CID_MSG_GET_LATEST_MSG_ID_RSP);
	  conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //数据最终会在conn.Buddy所在的io线程中发送出去。
      }
      else{
          log("invalid sessionType. userId=%u, peerId=%u, sessionType=%u", nUserId, nPeerId, nType);
      }
  }
  else{ 
      log("parse pb failed");
  }
  }
};
