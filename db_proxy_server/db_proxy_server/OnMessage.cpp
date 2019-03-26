/*
 * File    : db_proxy_server/main.cpp
 *
 * Author  : Ys Li
 */

#include <iostream>
#include "../muduo/base/Mutex.h"

#include "OnMessage.h"
#include "../base/ImPduBase.h"
#include "HandlerMap.h"
#include "../base/ThreadPool.h"
#include "../base/pb/protocol/IM.BaseDefine.pb.h"

using std::cout;
using std::endl;

extern CThreadPool g_thread_pool;

muduo::MutexLock s_lock;

void HandlePdu(CImPdu* pdu, const muduo::net::TcpConnectionPtr& conn);


void OnMessage(const muduo::net::TcpConnectionPtr& conn,
				Buffer* buf,
				Timestamp receiveTime)
{
  //读取数据
  //解析数据包
  //调用Handle
  cout << "new message..." << endl;
  
  CImPdu* pPdu = NULL;
  try{
    while ( pPdu = CImPdu::ReadPdu(buf)){
      uint32_t pdu_len = pPdu->GetLength();

      HandlePdu(pPdu, conn);  //pPdu已在此处交给Handler处理（包括生命期）
      pPdu = NULL;
      }
   }
   catch (CPduException& ex) {
     log("!!!catch exception, sid=%u, cid=%u, err_code=%u, err_msg=%s, close the connection ",
	 ex.GetServiceId(), ex.GetCommandId(), ex.GetErrorCode(), ex.GetErrorMsg());
     if (pPdu) {
       delete pPdu;
       pPdu = NULL;
     }
     conn->forceClose();
  }
}



void HandlePdu(CImPdu* pdu, const muduo::net::TcpConnectionPtr& conn)
{
	
  if (pdu->GetCommandId() == IM::BaseDefine::CID_OTHER_HEARTBEAT)
    return;

  pdu_handler_t handler;
  if(CHandlerMap::getInstance()->GetHandler(pdu->GetCommandId(), handler)){
      CTask* pTask = new CProxyTask(handler, pdu, conn);
      g_thread_pool.AddTask(pTask);     //任务是在线程池中完成的，但最终数据的发送会在conn所在的io线程中完成。
  }
  else 
      log("no handler for packet type: %d", pdu->GetCommandId());
}
