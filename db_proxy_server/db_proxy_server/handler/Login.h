
#ifndef LOGIN_H_
#define LOGIN_H_

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {

	void doLogin(CImPdu* pPdu, const TcpConnectionPtr&                                                 conn);

};


#endif /* LOGIN_H_ */
