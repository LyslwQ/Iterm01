#include <list>
#include <vector>


#include "RecentSession.h"
#include "../DBPool.h"
#include "../CachePool.h"
#include "../model/SessionModel.h"

#include "../model/UserModel.h"
#include "../model/GroupModel.h"
#include "../../base/pb/protocol/IM.Buddy.pb.h"


using namespace std;

namespace DB_PROXY {
/**
*  ��ȡ����Ự�ӿ�
*
*  @param pPdu      �յ���packet��ָ��
*  @param conn      �ð����������Ӷ���
*/
//��Ӧ���ӵ�outputBuffer_���Բ�����ʽ��������
//������õĽ��д��outputBuffer_�������Զ����ͳ�ȥ��
void getRecentSession(CImPdu* pPdu, const TcpConnectionPtr& conn)
{

  IM::Buddy::IMRecentContactSessionReq msg;
  IM::Buddy::IMRecentContactSessionRsp msgResp;
  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      CImPdu* pPduResp = new CImPdu;

      uint32_t nUserId = msg.user_id();
      uint32_t nLastTime = msg.latest_update_time();

      //��ȡ�����ϵ���б�
      list<IM::BaseDefine::ContactSessionInfo> lsContactList;
      CSessionModel::getInstance()->getRecentSession(nUserId, nLastTime, lsContactList);
      msgResp.set_user_id(nUserId);
      for (auto it = lsContactList.begin(); it != lsContactList.end(); ++it){
          IM::BaseDefine::ContactSessionInfo* pContact = msgResp.add_contact_session_list();
	  //            *pContact = *it;
	  pContact->set_session_id(it->session_id());
	  pContact->set_session_type(it->session_type());
	  pContact->set_session_status(it->session_status());
	  pContact->set_updated_time(it->updated_time());
          pContact->set_latest_msg_id(it->latest_msg_id());
	  pContact->set_latest_msg_data(it->latest_msg_data());
	  pContact->set_latest_msg_type(it->latest_msg_type());
	  pContact->set_latest_msg_from_user_id(it->latest_msg_from_user_id());
      }

      log("userId=%u, last_time=%u, count=%u", nUserId, nLastTime, msgResp.contact_session_list_size());

      msgResp.set_attach_data(msg.attach_data());
      pPduResp->SetPBMsg(&msgResp);
      pPduResp->SetSeqNum(pPdu->GetSeqNum());
      pPduResp->SetServiceId(IM::BaseDefine::SID_BUDDY_LIST);
      pPduResp->SetCommandId(IM::BaseDefine::CID_BUDDY_LIST_RECENT_CONTACT_SESSION_RESPONSE);
      conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //�������ջ���conn.Buddy���ڵ�io�߳��з��ͳ�ȥ��
  } 
  else{
      log("parse pb failed");
  }
}

/**
*  ɾ���Ự�ӿ�
*
*  @param pPdu      �յ���packet��ָ��
*  @param conn      �ð����������Ӷ���
*/
void deleteRecentSession(CImPdu* pPdu, const TcpConnectionPtr& conn)
{
  IM::Buddy::IMRemoveSessionReq msg;
  IM::Buddy::IMRemoveSessionRsp msgResp;

  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      CImPdu* pPduResp = new CImPdu;

      uint32_t nUserId = msg.user_id();
      uint32_t nPeerId = msg.session_id();
      IM::BaseDefine::SessionType nType = msg.session_type();
      if (IM::BaseDefine::SessionType_IsValid(nType)){
          bool bRet = false;
	  uint32_t nSessionId = CSessionModel::getInstance()->getSessionId(nUserId, nPeerId, nType, false);
	  if (nSessionId != INVALID_VALUE) {
	      bRet = CSessionModel::getInstance()->removeSession(nSessionId);
	      // if remove session success, we need to clear the unread msg count
	      if (bRet){
                  CUserModel::getInstance()->clearUserCounter(nUserId, nPeerId, nType);
	      }
	  }
	  log("userId=%d, peerId=%d, result=%s", nUserId, nPeerId, bRet ? "success" : "failed");

	  msgResp.set_attach_data(msg.attach_data());
	  msgResp.set_user_id(nUserId);
          msgResp.set_session_id(nPeerId);
	  msgResp.set_session_type(nType);
	  msgResp.set_result_code(bRet ? 0 : 1);
	  pPduResp->SetPBMsg(&msgResp);
          pPduResp->SetSeqNum(pPdu->GetSeqNum());
	  pPduResp->SetServiceId(IM::BaseDefine::SID_BUDDY_LIST);
	  pPduResp->SetCommandId(IM::BaseDefine::CID_BUDDY_LIST_REMOVE_SESSION_RES);
	  conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //�������ջ���conn.Buddy���ڵ�io�߳��з��ͳ�ȥ��
      }
      else{
          log("invalied session_type. userId=%u, peerId=%u, seseionType=%u", nUserId, nPeerId, nType);
      }
  }
  else {
      log("parse pb failed");
  }
  }

};

