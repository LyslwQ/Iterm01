
#ifndef FRIEND_SHIP_H_
#define FRIEND_SHIP_H_

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {

	void getRecentSession(CImPdu* pPdu, const TcpConnectionPtr& conn);

	void deleteRecentSession(CImPdu* pPdu, const TcpConnectionPtr& conn);

};


#endif /* FRIEND_SHIP_H_ */
