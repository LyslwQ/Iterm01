#include <list>

#include "../../base/HttpClient.h"
#include "../SyncCenter.h"
#include "Login.h"
#include "../model/UserModel.h"
#include "../../base/TokenValidator.h"
#include "../../base/jsoncpp/json/json.h"
#include "Common.h"
#include "../../base/pb/protocol/IM.Server.pb.h"
#include "../../base/Base64.h"
#include "InterLogin.h"
#include "ExterLogin.h"
#include "../../base/util.h"

CInterLoginStrategy g_loginStrategy;

hash_map<string, list<uint32_t> > g_hmLimits;
CLock g_cLimitLock;

namespace DB_PROXY {

void doLogin(CImPdu* pPdu, const TcpConnectionPtr& conn)
{

  CImPdu* pPduResp = new CImPdu;

  IM::Server::IMValidateReq msg;     //���ڽ��롰��֤�������ݡ�
  IM::Server::IMValidateRsp msgResp; //���ڱ��롰��֤�ָ����ݡ�
  if (msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength())){
      string strDomain = msg.user_name();
      string strPass = msg.password();

      msgResp.set_user_name(strDomain);
      msgResp.set_attach_data(msg.attach_data());

      {
          CAutoLock cAutoLock(&g_cLimitLock);
	  list<uint32_t>& lsErrorTime = g_hmLimits[strDomain];
	  uint32_t tmNow = time(NULL);
	  /*
            ���ڵ�¼����ĸ��������˵С����ȷ�ĸ��ʡ�
            ���Խ�����30���Ӻ�����¼�Ĺ������ڵ�¼�����������10��ʱ���С�
      	  */
	  
	  // �ж������������Ƿ����10
	  if (lsErrorTime.size() > 10){
              //�������������10�Σ����30���Ӻ�ļ�¼��
              auto itTime = lsErrorTime.begin();
	      for (; itTime != lsErrorTime.end(); ++itTime){
	          if (tmNow - *itTime > 30 * 60)
	          break;
              }
	      if (itTime != lsErrorTime.end())
	          lsErrorTime.erase(itTime, lsErrorTime.end());
              
	      itTime = lsErrorTime.begin();
              //��30�����ڴ���Ĵ�������10�Σ��������¼�����ش���������ࡣ
	      if (lsErrorTime.size() >= 10){
	          msgResp.set_result_code(6); //CID_LOGIN_RES_MSGSERVER
		  msgResp.set_result_string("�û���/����������̫��");
	          pPduResp->SetPBMsg(&msgResp);
		  pPduResp->SetSeqNum(pPdu->GetSeqNum());
		  pPduResp->SetServiceId(IM::BaseDefine::SID_OTHER);
		  pPduResp->SetCommandId(IM::BaseDefine::CID_OTHER_VALIDATE_RSP);
                  conn->send(pPduResp->GetBuffer(), pPduResp->GetLength()); 
	          return;
	      }
	  }
      } 

	  log("%s request login.", strDomain.c_str());

	  IM::BaseDefine::UserInfo cUser;

	  if (g_loginStrategy.doLogin(strDomain, strPass, cUser)){
	      IM::BaseDefine::UserInfo* pUser = msgResp.mutable_user_info();
	      pUser->set_user_id(cUser.user_id());
	      pUser->set_user_gender(cUser.user_gender());
	      pUser->set_department_id(cUser.department_id());
	      pUser->set_user_nick_name(cUser.user_nick_name());
	      pUser->set_user_domain(cUser.user_domain());
	      pUser->set_avatar_url(cUser.avatar_url());

	      pUser->set_email(cUser.email());
	      pUser->set_user_tel(cUser.user_tel());
	      pUser->set_user_real_name(cUser.user_real_name());
	      pUser->set_status(0);

	      pUser->set_sign_info(cUser.sign_info());

	      msgResp.set_result_code(0);
	      msgResp.set_result_string("�ɹ�");

	      //�����½�ɹ�������������¼
              CAutoLock cAutoLock(&g_cLimitLock);
	      list<uint32_t>& lsErrorTime = g_hmLimits[strDomain];
	      lsErrorTime.clear();
	  }
	  else{
	      //������󣬼�¼һ�ε�½ʧ��
	      uint32_t tmCurrent = time(NULL);
	      CAutoLock cAutoLock(&g_cLimitLock);
	      list<uint32_t>& lsErrorTime = g_hmLimits[strDomain];
	      lsErrorTime.push_front(tmCurrent);

	      log("get result false");
	      msgResp.set_result_code(1);
	      msgResp.set_result_string("�û���/�������");
	  }
      }
      else{
          msgResp.set_result_code(2);
	  msgResp.set_result_string("������ڲ�����");
      }

      pPduResp->SetPBMsg(&msgResp);
      pPduResp->SetSeqNum(pPdu->GetSeqNum());
      pPduResp->SetServiceId(IM::BaseDefine::SID_OTHER);
      pPduResp->SetCommandId(IM::BaseDefine::CID_OTHER_VALIDATE_RSP);
      conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //�������ջ���conn.Buddy���ڵ�io�߳��з��ͳ�ȥ��
  }

};

