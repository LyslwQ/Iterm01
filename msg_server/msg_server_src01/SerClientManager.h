#ifndef    SER_CLIENT_MANAGER_H_   
#define    SER_CLIENT_MANAGER_H_

#include <vector>
#include <string>
#include <functional>
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/Buffer.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>

using std::vector;
using std::string;

typedef muduo::net::TcpConnectionPtr      TcpConnectionPtr;
typedef muduo::net::ConnectionCallback    ConnectionCallback;
typedef muduo::net::MessageCallback       MessageCallback;
typedef muduo::net::Buffer                Buffer;
typedef muduo::Timestamp                  Timestamp;
typedef muduo::net::TcpClient             TcpClient;
typedef muduo::net::EventLoop             EventLoop;

struct TcpClientInfo
{
  TcpClient*  m_client;
   //用于表示该客户端是否可以正常收发数据
   //（是应用层的实现，接收到“停止接收数据”的pdu时，该位有效）
  time_t      m_last_send_time;
  time_t      m_last_recv_time;
  ~TcpClientInfo(){ delete m_client;} //析构函数，转用于析构指针成员
}

class SerClientManager
{
public:
  //todo:初期使用单线程版本(多个client时，共用一个loop)
  SerClientManager(const string& serve_ip, uint16_t server_port, 
                   uint32_t client_count=2);

  ~SerClientManager();
  void start();

  void setConnCallback(const ConnectionCallback& cb) { connectionCallback_ = cb;}
  void setMessCallback(const MessageCallback& cb) {messageCallback_ = cb;}
  virtual void onTimer();
  TcpClientInfo* get_server_client_in_range()
  virtual void HandlePdu(CImPdu* pPdu,const TcpClientInfo* conn) {}
private:

  vector<TcpClientInfo*>       m_client_list;
  map<string, TcpClientInfo*>  m_client_map; //用于检索。
  ConnectionCallback    connectionCallback_;    //连接建立完成，连接关闭回调
  MessageCallback       messageCallback_;       //消息回调
 // callback_t        writeCompleteCallback_; //可写回调

    
  string    m_server_ip;
  uint16_t  m_server_port;

  uint32_t  m_client_count;  //连接服务器的客户端个数
  uint32_t  m_idle_count;    //空闲的客户端个数
  uint32_t  m_timer_interval;//定时器的间隔
  EventLoop* m_pLoop;
};

#endif
