#ifndef    SER_CLIENT_MANAGER_H_
#define    SER_CLIENT_MANAGER_H_

#include <list>
#include <string>
#include <functional>
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop>

using std::list;
using std::string;

class TcpConnectionPtr;
typedef std::function<void (const TcpConnectionPtr&)> callback_t;

typedef std::function<void (const TcpConnectionPtr&,
                            Buffer*,
                            Timestamp)> MessageCallback_t;

typedef muduo::net::TcpClient  TcpClient;
typedef muduo::net::EventLoop  EventLoop;

class SerClientManager
{
public:
  //todo:初期使用单线程版本
  SerClientManager(string& serve_ip, uint16_t server_port, uint32_t client_count = 1)
  : m_server_ip(serve_ip), m_server_port(server_port),
    m_client_count(client_count)

  void start();

  void setConnCallback(const callback_t& cb) { connectionCallback_ = cb;}
  void setMessCallback(const MessageCallback_t& cd) {messageCallback_ = cb;}

private:

  list<TcpClient*>  m_client_list;
  callback_t        connectionCallback_;    //连接建立完成，连接关闭回调
  MessageCallback   messageCallback_;       //消息回调
 // callback_t        writeCompleteCallback_; //可写回调

  
  string    m_server_ip;
  uint16_t  m_server_port;

  uint32_t  m_client_count;  //连接服务器的客户端个数
  uint32_t  m_idle_count;    //空闲的客户端个数
  
  EventLoop* m_pLoop;
};

#endif
