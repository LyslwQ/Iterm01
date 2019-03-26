#ifndef __FILEACTION_H__
#define __FILEACTION_H__

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;


namespace DB_PROXY {
    void hasOfflineFile(CImPdu* pPdu, const TcpConnectionPtr& conn);
    void addOfflineFile(CImPdu* pPdu, const TcpConnectionPtr& conn);
    void delOfflineFile(CImPdu* pPdu, const TcpConnectionPtr& conn);
};

#endif /*defined(__FILEACTION_H__) */
