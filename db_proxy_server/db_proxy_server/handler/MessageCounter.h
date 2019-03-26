
#ifndef MESSAGECOUNTER_H_
#define MESSAGECOUNTER_H_

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {
	/*
	 * input: @1.待处理的pPdu
	 *        @2.对应连接的发送缓存区
	 */
	void getUnreadMsgCounter(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void clearUnreadMsgCounter(CImPdu* pPdu, const TcpConnectionPtr& conn);

	void setDevicesToken(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void getDevicesToken(CImPdu* pPdu, const TcpConnectionPtr& conn);
};


#endif /* MESSAGECOUNTER_H_ */
