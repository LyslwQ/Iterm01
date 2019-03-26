#include <iostream>
#include <muduo/net/InetAddress.h>
#include "../base/ImPduBase.h"
#include "../base/pb/protocol/IM.BaseDefine.pb.h"

#include "SerClientManager.h"

using std::cout;
using std::endl;
using namespace std::placeholders;

typedef muduo::net::InetAddress  InetAddress;

void defaultConnCallback(const TcpConnectionPtr& conn)
{
  if (conn->connected()){
      printf("onConnection(): new connection [%s] from %s\n",
              conn->name().c_str(),
              conn->peerAddress().toIpPort().c_str());
   // conn->send(message);
  }
  else{
      printf("onConnection(): connection [%s] is down\n",
             conn->name().c_str());
  }
}


void defaultMessageCallback(const TcpConnectionPtr& conn,
                            Buffer* buf,
                            Timestamp receiveTime)
{
  printf("onMessage(): received %zd bytes from connection [%s] at %s\n",
         buf->readableBytes(),
         conn->name().c_str(),
         receiveTime.toFormattedString().c_str());

 // printf("onMessage(): [%s]\n", buf->retrieveAllAsString().c_str());
  CImPdu* pPdu = NULL;
  try{
      while ( pPdu = CImPdu::ReadPdu(buf)){
          uint32_t pdu_len = pPdu->GetLength();

          HandlePdu(pPdu, conn);  //pPdu已在此处交给Handler处理（包括生命期）
          pPdu = NULL;
      }
   }
   catch (CPduException& ex) {
       log("!!!catch exception, sid=%u, cid=%u, err_code=%u, 
            err_msg=%s, close the connection ",
            ex.GetServiceId(), ex.GetCommandId(), 
            ex.GetErrorCode(), ex.GetErrorMsg());
       if (pPdu) {
           delete pPdu;
           pPdu = NULL;
       }
       conn->forceClose();
  }
}




SerClientManager::SerClientManager(const string& serve_ip, 
                                   uint16_t server_port, 
                                   uint32_t client_count)  
                                   : m_server_ip(serve_ip), m_server_port(server_port),
                                     m_client_count(client_count)
{
  cout << "server addr--" << m_server_ip 
       << ":" << m_server_port << endl;

  cout << "client count:" << m_client_count << endl;
  m_pLoop = new EventLoop;
  //设置默认的callback
  messageCallback_     = defaultMessageCallback;
  connectionCallback_  = defaultConnCallback;
}


void SerClientManager::start()
{
  TcpClient* p = NULL;
  for(uint32_t i=0; i < m_client_count; ++i){
      p = new TcpClient(m_pLoop,InetAddress(m_server_ip, m_server_port), "defaultName");
      if(p == nullptr)
          continue;
      p->setMessageCallback(messageCallback_);
      p->setConnectionCallback(connectionCallback_);
     
      p->enableRetry();  //当连接被断开后会尝试去重新连接（todo：没有限定重联的次数）
      p->connect();      
      m_client_list.push_back(p);
  } 
  cout << "loop..." << endl; 
  m_pLoop->loop();  //开始事件循环
}


SerClientManager::~SerClientManager()
{
  list<TcpClient*>::iterator it = m_client_list.begin();
  for(; it != m_client_list.end(); ++it)
      delete *it;
  delete m_pLoop;
}
