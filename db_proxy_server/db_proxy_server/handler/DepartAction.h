
#ifndef __DEPARTACTION_H__
#define __DEPARTACTION_H__
#include "../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;


namespace DB_PROXY {
    
    void getChgedDepart(CImPdu* pPdu, const TcpConnectionPtr& conn);
};


#endif /*defined(__DEPARTACTION_H__) */
