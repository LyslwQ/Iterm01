#include <muduo/net/InetAddress.h>
#include "SerClientManager.h"

typedef muduo::net::InetAddress  InetAddress;

SerClientManager::SerClientManager(string& serve_ip, 
                                   uint16_t server_port, 
                                   uint32_t client_count = 1)  
                                   : m_server_ip(serve_ip), m_server_port(server_port),
                                     m_client_count(client_count)
{
  m_pLoop = new EventLoop_t; 
}


SerClientManager::start()
{
  TcpClient* p = NULL;
  for(uint32_t i=0; i < m_client_count; ++i){
      p = new TcpClient(m_pLoop,InetAddress(m_server_ip, m_server_port));
      p->setMessageCallback(messagesCallback_);
      p->setConnectionCallback(connectionCallback_);
      p->enableRetry();
      p->connect();      
      m_client_list.push_back(p);
  }  
  m_pLoop->loop();  //开始事件循环
}


SerClientManager::~SerClientManager()
{
  delete m_pLoop;
}
