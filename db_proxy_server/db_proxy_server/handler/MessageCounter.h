
#ifndef MESSAGECOUNTER_H_
#define MESSAGECOUNTER_H_

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {
	/*
	 * input: @1.�������pPdu
	 *        @2.��Ӧ���ӵķ��ͻ�����
	 */
	void getUnreadMsgCounter(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void clearUnreadMsgCounter(CImPdu* pPdu, const TcpConnectionPtr& conn);

	void setDevicesToken(CImPdu* pPdu, const TcpConnectionPtr& conn);
	void getDevicesToken(CImPdu* pPdu, const TcpConnectionPtr& conn);
};


#endif /* MESSAGECOUNTER_H_ */
