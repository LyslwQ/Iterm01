#include <muduo/net/TcpServer.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/EventLoop.h>

#include "msg_server.h"
#include "EncDec.h"
#include "ConfigFileReader.h"
#include "MsgConn.h"
#include "LoginServConn.h"
#include "RouteServConn.h"
#include "DBServConn.h"
#include "PushServConn.h"
#include "FileServConn.h"
//#include "version.h"

#define DEFAULT_CONCURRENT_DB_CONN_CNT  10
const uint16_t  LOOP_POOL_NUM = 2;  //loop_pool中的loop个数。取决于msgserver的个数。
typedef muduo::net::TcpServer            TcpServer;
typedef muduo::net::EventLoop            EventLoop;
typedef muduo::net::InetAddress          InetAddress;
typedef muduo::net::EventLoopThreadPool  EventLoopThreadPool;
std::list<IMServer*>  g_server_list;

CAes *pAes;
//加static属性，将变量隐藏在该源文件中。
static serv_info_t*  m_db_server_list    = nullptr;
static serv_info_t*  m_login_server_list = nullptr;
static serv_info_t*  m_route_server_list = nullptr;
static serv_info_t*  m_push_server_list  = nullptr;
static serv_info_t*  m_file_server_list  = nullptr;

static   uint32_t      m_db_server_count    = 0;
static   uint32_t      m_login_server_count = 0;
static   uint32_t      m_route_server_count = 0;
static   uint32_t      m_push_server_count  = 0;
static   uint32_t      m_file_server_count  = 0;

EventLoop*                   g_pTimerLoop = nullptr;
static EventLoopThreadPool*  g_pLoopPool  = nullptr;

void read_other_server_config(const CConfigFileReader& config_file)
{
  //get server_ip server_port
  uint32_t      db_server_count;
  serv_info_t*  db_server_list;
  db_server_list = read_server_config(&config_file, 
                                      "DBServerIP", "DBServerPort", 
                                       db_server_count);

  m_login_server_list = read_server_config(&config_file,  
                                           "LoginServerIP", 
                                           "LoginServerPort", 
                                           m_login_server_count);

  m_route_server_list = read_server_config(&config_file, 
                                           "RouteServerIP", 
                                           "RouteServerPort", 
                                            m_route_server_count);

  m_push_server_list = read_server_config(&config_file, 
                                          "PushServerIP",
                                          "PushServerPort", 
                                           m_push_server_count);
    
  m_file_server_list = read_server_config(&config_file, 
                                          "FileServerIP",
                                          "FileServerPort", 
                                          m_file_server_count);
  // 必须至少配置2个DBServer实例, 一个用于用户登录业务，一个用于其他业务
  // 这样当其他业务量非常繁忙时，也不会影响客服端的登录验证
  // 建议配置4个实例，这样更新DBServer时，不会影响业务
  if (db_server_count < 2) {
      log("DBServerIP need 2 instance at lest ");
      return 1;
  }

  // 配置到DBServer的并发连接数目,
  // 如果用户没有配置每个dbServer的并发连接数，则使用默认值
  m_db_server_count = db_server_count * DEFAULT_CONCURRENT_DB_CONN_CNT;
  char* db_conn_count = config_file.GetConfigName("ConcurrentDBConnCnt");
  if (db_conn_count) 
      m_db_server_count = db_server_count * atoi(db_conn_count);

  m_db_server_list = new serv_info_t [ m_db_server_count];
  for (uint32_t i = 0; i < db_server_count2; i++) {
      //均匀地将db_server_addr分配给每个连接。
      m_db_server_list[i].server_ip = db_server_list[i / m_db_server_count].server_ip.c_str();
      m_db_server_list[i].server_port = db_server_list[i / m_db_server_count].server_port;
  }


}


//目前，每个server只是单线程版本，后期可改为多线程
bool start_msg_server(char* ip, char* str_port)
{
  if (!ip || !str_port) {
      log("config file miss, exit... ");
      return false;
  }
  g_pLoopPool = new EventLoopThreadPool(g_pTimerLoop,"loopPool");
  g_pLoopPool->setThreadNum(LOOP_POOL_NUM);
  g_pLoopPool->start();
  uint16_t port = atoi(str_port);

  //在启动msgServer或者是连接其他server之前，
  //必须确保所有的配置信息是完整的和正确的。
  CStrExplode ip_list(ip, ';');
  for (uint32_t i = 0; i < ip_list.GetItemCnt(); i++) {
      EventLoop* p_loop = g_pLoopPool->getNextLoop();
      IMServer* p_server = new IMServer(ip_list.GetItem(i), port, p_loop, serv_name+i);
      p_server->start();
      p_loop->loop();
      g_loop_list.push_back(p_loop);
      g_server_list.push_back(p_server);
      printf("server start listen on: %s:%d\n", ip_list.GetItem(i), port);
      printf("now enter the event loop...\n");
  }
  return true;
}




// for client connect in
void msg_serv_callback(void* callback_data, uint8_t msg, uint32_t handle, void* pParam)
{
	if (msg == NETLIB_MSG_CONNECT)
	{
		CMsgConn* pConn = new CMsgConn();
		pConn->OnConnect(handle);
	}
	else
	{
		log("!!!error msg: %d ", msg);
	}
}



int main(int argc, char* argv[])
{
  if ((argc == 2) && (strcmp(argv[1], "-v") == 0)) {
      //printf("Server Version: MsgServer/%s\n", VERSION);
      printf("Server Build: %s %s\n", __DATE__, __TIME__);
      return 0;
  }

  signal(SIGPIPE, SIG_IGN);
  srand(time(NULL));

  log("MsgServer max files can open: %d ", getdtablesize());

  CConfigFileReader config_file("msgserver.conf");

  char* listen_ip = config_file.GetConfigName("ListenIP");
  char* str_listen_port = config_file.GetConfigName("ListenPort");
  char* ip_addr1 = config_file.GetConfigName("IpAddr1");	// 电信IP
  char* ip_addr2 = config_file.GetConfigName("IpAddr2");	// 网通IP
  char* str_max_conn_cnt = config_file.GetConfigName("MaxConnCnt");
  char* str_aes_key = config_file.GetConfigName("aesKey");
  
  if (!str_aes_key || strlen(str_aes_key)!=32) {
      log("aes key is invalied");
      return -1;
  }
  pAes = new CAes(str_aes_key);
  //加载其他server的配置信息。
  read_other_server_config(config_file);  
  init_msg_server();  
  g_pTimerLoop = new EventLoop;
  //启动服务器
  if( !start_msg_server(char* ip, char* port))
      return -1;
        




  init_file_serv_conn(file_server_list, file_server_count);

  init_db_serv_conn(db_server_list2, db_server_count2, concurrent_db_conn_cnt);

  init_login_serv_conn(login_server_list, login_server_count, 
                       ip_addr1, ip_addr2, listen_port, max_conn_cnt);

  init_route_serv_conn(route_server_list, route_server_count);

  init_push_serv_conn(push_server_list, push_server_count);
  printf("now enter the event loop...\n");
    
  writePid();

  g_pTimerLoop->loop();

  return 0;
}
