#ifndef DB_SERVER_CLIENT_H_
#define DB_SERVER_CLIENT_H_

#include "SerClientManager.h"

static CGroupChat*	s_group_chat = NULL;
static CFileHandler*    s_file_handler = NULL;
//连接DBServ的连接总数
static uint32_t		g_db_client_count = 0;	
//连接到DBServ，优先处理登录业务的连接总数。
static uint32_t	        g_db_client_login_count = 0;

class DBSerClient: public SerClientManager
{
public:
  DBSerClient(const char* servIp, uint16_t serPort, 
              uint16_t clientCount, uint16_t concur_conn_cnt);
  virtual void HandlePdu(CImPdu* pPdu,const TcpConnectionPtr& conn);
  TcpClientInfo* get_db_serv_client_for_login();
  TcpClientInfo* get_db_serv_client();
private:
 
};
