
#ifndef __USER_ACTION_H__
#define __USER_ACTION_H__

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {

	/*
	 * input：@1. 待处理的pPdu。
	 *        @2. 对应连接的outputBuffer_.
	 */
	
	void getUserInfo(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void getChangedUser(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void changeUserSignInfo(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void doPushShield(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void doQueryPushShield(CImPdu* pPdu, const TcpConnectionPtr& conn);
};


#endif /* __USER_ACTION_H__ */
