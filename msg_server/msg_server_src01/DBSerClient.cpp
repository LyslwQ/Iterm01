#include "DBSerClient.h"

DBSerClient::DBSerClient(const char* server_ip, uint16_t server_port, 
                         uint16_t client_count, uint16_t concur_conn_cnt)
                        :SerClientManager(server_ip, server_port, client_count)
{
  uint16_t total_db_instance = client_count / concur_conn_cnt;
  g_db_client_login_count = (total_db_instance / 2) * concur_conn_cnt;

  s_group_chat = CGroupChat::GetInstance();
  s_file_handler = CFileHandler::getInstance();
}


void DBSerClient::HandlePdu(CImPdu* pPdu,const TcpClientInfo& conn)
{
  //todo
}


TcpClientInfo* DBSerClient::get_db_serv_client_for_login()
{
  // 先获取login业务的实例，没有就去获取其他业务流程的实例
   TcpClientInfo* pDBClient = get_server_client_in_range(0, g_db_server_login_count);
   if (!pDBConn) 
       pDBConn = get_server_client_in_range(g_db_server_login_count, 
                                            g_db_server_count);
   return pDBClient;
}


TcpclientInfo* DBSerClient::get_db_serv_client()
{
  TcpClientInfo* pDBClient = get_server_client_in_range(g_db_server_login_count, 
                                                        g_db_server_count);
  if (!pDBConn)
       pDBConn = get_server_client_in_range(0, g_db_server_login_count);
   return pDBClient;
}

