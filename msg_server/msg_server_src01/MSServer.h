#ifndef MSSERVER_H_
#define MSSERVER_H_

#include <memory>

#include <muduo/net/TcpServer.h>

#include "CMsgConn.h"

typedef  map<TcpConntionPtr, const shared_ptr<CMsgConn>> conn_msgConn_t; 

class MSServer final
{
public:
    MSServer(const char* ip, uint16_t port, EventLoop* loop, const char* name);
    ~MSServer();

    MSServer(const MSServer& rhs) = delete;
    MSServer& operator =(const MSServer& rhs) = delete;

    bool start();
    void OnConnection(const TcpConntionPtr& conn);
    void OnTimer();
    void removeConn(const CMsgConn& cmsConn);

   // void GetSessions(std::list<std::shared_ptr<ClientSession>>& sessions);

private:
  shared_ptr<TcpServer>      server_;
  conn_msgConn_t             map_conn_msgConn_;
 
};
 
