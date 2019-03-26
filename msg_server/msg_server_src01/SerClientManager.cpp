#include <iostream>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Timestamp.h>
#include "SerClientManager.h"

using std::cout;
using std::endl;
using namespace std::placeholders;

typedef muduo::net::InetAddress  InetAddress;


//连接建立或者连接断开的回调
void defaultConnCallback(const TcpConnectionPtr& conn)
{
  if (conn->connected()){ //连接建立完成
      printf("onConnection(): new connection [%s] from %s\n",
              conn->name().c_str(),
              conn->peerAddress().toIpPort().c_str());
      //由于库的实现，只能这样间接的实现。
      list<TcpClientInfo*>::iterator it = m_client_list.begin();
      for(; it != m_client_list.end(); ++it){
          if(it->m_client->connection()->name() == conn->name())
              m_client_map[conn->name()] = *it;
   // conn->send(message);
  }
  else{//连接断开，从list中释放该client对象，并补充创建新的client
      printf("onConnection(): connection [%s] is down\n",
             conn->name().c_str());
      vector<TcpClientInfo*>::iterator it = m_client_list.begin();
      for(; it != m_client_list.end(); ++it){
          if( this == it->m_client){
              delete *it;  
            //  delete *it;
            //  m_client_list.erase(it);
          
          TcpClientInfo* p = new TcpClientInfo;
          p->m_client = new TcpClient(m_pLoop,
                                  InetAddress(m_server_ip, m_server_port), 
                                  Timestamp::now().toString()));
          p->m_client->setMessageCallback(messageCallback_);
          p->m_client->setConnectionCallback(connectionCallback_);

          p->m_client->enableRetry();  //当连接被断开后会尝试去重新连接（todo：没有限定重联的次数>）
          p->m_client->connect();
         // m_client_list.push_back(p); 
         *it = p;
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

  printf("onMessage(): [%s]\n", buf->retrieveAllAsString().c_str());
}




SerClientManager::SerClientManager(const string& serve_ip, 
                                   uint16_t server_port, 
                                   uint32_t client_count)  
                                   : m_server_ip(serve_ip), m_server_port(server_port),
                                     m_client_count(client_count), m_timer_interval(5)
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
      TcpClientInfo* pp = new TcpClientInfo;
      pp->m_client = p;
      m_client_list.push_back(p);
  } 
  cout << "loop..." << endl; 
  if(m_pLoop)
      m_pLoop->runEvery(m_timer_interval, std::bind(SerClientManager::onTimer,this)); //定时
  m_pLoop->loop();  //开始事件循环
}


SerClientManager::~SerClientManager()
{
  list<TcpClientInfo*>::iterator it = m_client_list.begin();
  for(; it != m_client_list.end(); ++it){
      delete *it;
  }
  delete m_pLoop;
}



//定时器，用于实现心跳包和检测服务器超时
void SerClientManager::onTimer()
{
  list<TcpClientInfo*>::iterator it = m_client_list.begin();
  for(; it != m_client_list.end(); ++it){
      if (Timestamp::now().secondsSinceEpoch() > 
          it->m_last_send_time + SERVER_HEARTBEAT_INTERVAL) { //超时发送心跳包
          IM::Other::IMHeartBeat msg;
          CImPdu pdu;
          pdu.SetPBMsg(&msg);
          pdu.SetServiceId(SID_OTHER);
          pdu.SetCommandId(CID_OTHER_HEARTBEAT);
          it->m_client->connect()->send(pdu->GetBuffer(), pdu->GetLength());
      }
      if (Timestamp::now().secondsSinceEpoch() > 
          it->m_last_recv_time + SERVER_TIMEOUT) {

          log("conn to db server timeout");
          it->m_client->disconnect(); //强制关闭连接
      }
  }
 // serv_check_reconnect();  //某些连接会因为异常被中断，需要定时创建补充连接对象。
}


// get a random db server client in the range [start_pos, stop_pos)
TcpClientInfo* get_server_client_in_range(uint32_t start_pos, 
                                          uint32_t stop_pos)
{
  //如果所在范围内没有可选客户端可选，则返回。
  if(m_client_list.size() < start_pos+1)
      return nullptr;

  while(true){
      int i = rand() % (stop_pos - start_pos) + start_pos;
      if( i+1 > m_client_list.size())
          continue;
      else{
          TcpClientInfo* pClient = static_cast<TcpClientInfo*>(m_client_list[i]);
          return pClient;
      } 
  }
}
