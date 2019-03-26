#include "MSServer.h"

using std::placeholders;

MSServer::MSServer(const char* ip, uint16_t port, EventLoop* loop, const char* name)
{
  InetAddress addr(ip, port);
  m_server.reset(new TcpServer(loop, addr, name, TcpServer::kReusePort));
  m_server->setConnectionCallback(std::bind(&MSServer::OnConnection, this, _1));  
}


void MSServer::start()
{
  init_msg_conn();

  m_server->start();
  loop->runEvery(5, std::bind(&MSServer::OnTimer, this));
}


//当server有新连接到来或连接断开时，会调用该函数
void MSServer::OnConnection(const TcpConntionPtr& conn)
{
  if (conn->connected()){
      shared_ptr<CMsgConn> p(new CMsgConn);
      map_conn_msgConn_[conn] = p;    
      conn->setMessageCallback(std::bind(&CMsgConn::onMessage, p.get(), _1, _2, _3)); 
      conn->setConnectionCallback(std::bind(&CMsgConn::onConnection, p.get(), _1)); 
      p->setServCallback(std::bind(&MSServer::removeConn, this));        
      p->setLoginTime(Timestamp::now());    
  }
}



void MSServer::OnTimer()
{
  conn_msgConn_t::iterator it = map_conn_msgConn_.begin();
  shared_ptr<CMsgConn> pConn;
  //以毫秒为单位。
  int64_t cur_time = Timestamp::now().microSecondsSinceEpoch()/1000;

  for (; it != map_conn_msgConn_.end(); ++it) {

      pConn = static_cast<shared_ptr<CMsgConn>>(it->second);
      pConn->OnTimer(cur_time);
  }

  if (cur_time > g_last_stat_tick + LOG_MSG_STAT_INTERVAL) {
      g_last_stat_tick = cur_time;
      log("up_msg_cnt=%u, up_msg_miss_cnt=%u, down_msg_cnt=%u, down_msg_miss_cnt=%u ",
           g_up_msg_total_cnt, g_up_msg_miss_cnt,
           g_down_msg_total_cnt, g_down_msg_miss_cnt);
  }
}


//当某个客户端连接释放之后，会自动调用该函数。
void MSServer::removeConn(const CMsgConn& cmsConn)
{
  conn_msgConn_t::iterator it =  map_conn_msgConn_.find(cmsConn);
  if(it != map_conn_msgConn_.end())
      map_conn_msgConn_.erase(it);
}



static void signal_handler_usr1(int sig_no)
{
  if (sig_no == SIGUSR1) {
      log("receive SIGUSR1 ");
      g_up_msg_total_cnt = 0;
      g_up_msg_miss_cnt = 0;
      g_down_msg_total_cnt = 0;
      g_down_msg_miss_cnt = 0;
  }
}


static void signal_handler_usr2(int sig_no)
{
  if (sig_no == SIGUSR2) {
      log("receive SIGUSR2 ");
      g_log_msg_toggle = !g_log_msg_toggle;
  }
}


static void signal_handler_hup(int sig_no)
{
  if (sig_no == SIGHUP) {
      log("receive SIGHUP exit... ");
      exit(0);
  }
}

