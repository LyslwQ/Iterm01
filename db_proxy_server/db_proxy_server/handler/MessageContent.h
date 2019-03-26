#ifndef MESSAGECOUTENT_H_
#define MESSAGECOUTENT_H_

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {

	void getMessage(CImPdu* pPdu, const TcpConnectionPtr& conn);

	void sendMessage(CImPdu* pPdu, const TcpConnectionPtr& conn);

	void getMessageById(CImPdu* pPdu, const TcpConnectionPtr& conn);

	void getLatestMsgId(CImPdu* pPdu, const TcpConnectionPtr& conn);
};

#endif /* MESSAGECOUTENT_H_ */
