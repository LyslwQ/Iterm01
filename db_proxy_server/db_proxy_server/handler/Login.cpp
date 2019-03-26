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

  IM::Server::IMValidateReq msg;     //用于解码“验证请求数据”
  IM::Server::IMValidateRsp msgResp; //用于编码“验证恢复数据”
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
            由于登录错误的概率相对来说小于正确的概率。
            所以将清理30分钟后错误记录的工作放在登录错误次数大于10次时进行。
      	  */
	  
	  // 判断密码错误次数是否大于10
	  if (lsErrorTime.size() > 10){
              //若错误次数大于10次，清除30分钟后的记录。
              auto itTime = lsErrorTime.begin();
	      for (; itTime != lsErrorTime.end(); ++itTime){
	          if (tmNow - *itTime > 30 * 60)
	          break;
              }
	      if (itTime != lsErrorTime.end())
	          lsErrorTime.erase(itTime, lsErrorTime.end());
              
	      itTime = lsErrorTime.begin();
              //若30分钟内错误的次数超过10次，则结束登录，返回错误次数过多。
	      if (lsErrorTime.size() >= 10){
	          msgResp.set_result_code(6); //CID_LOGIN_RES_MSGSERVER
		  msgResp.set_result_string("用户名/密码错误次数太多");
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
	      msgResp.set_result_string("成功");

	      //如果登陆成功，则清除错误记录
              CAutoLock cAutoLock(&g_cLimitLock);
	      list<uint32_t>& lsErrorTime = g_hmLimits[strDomain];
	      lsErrorTime.clear();
	  }
	  else{
	      //密码错误，记录一次登陆失败
	      uint32_t tmCurrent = time(NULL);
	      CAutoLock cAutoLock(&g_cLimitLock);
	      list<uint32_t>& lsErrorTime = g_hmLimits[strDomain];
	      lsErrorTime.push_front(tmCurrent);

	      log("get result false");
	      msgResp.set_result_code(1);
	      msgResp.set_result_string("用户名/密码错误");
	  }
      }
      else{
          msgResp.set_result_code(2);
	  msgResp.set_result_string("服务端内部错误");
      }

      pPduResp->SetPBMsg(&msgResp);
      pPduResp->SetSeqNum(pPdu->GetSeqNum());
      pPduResp->SetServiceId(IM::BaseDefine::SID_OTHER);
      pPduResp->SetCommandId(IM::BaseDefine::CID_OTHER_VALIDATE_RSP);
      conn->send(pPduResp->GetBuffer(), pPduResp->GetLength());  //数据最终会在conn.Buddy所在的io线程中发送出去。
  }

};

