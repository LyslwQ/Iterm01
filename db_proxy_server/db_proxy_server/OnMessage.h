/*
 * File    : db_proxy_server/main.cpp
 *
 * Author  : Ys Li
 */
#include <boost/shared_ptr.hpp>
#include "../muduo/net/Callbacks.h"
#include "../muduo/net/TcpConnection.h"
#include "../muduo/net/Buffer.h"
#include "../muduo/base/Timestamp.h"

typedef muduo::net::Buffer         Buffer;
typedef muduo::Timestamp           Timestamp;

void OnMessage(const muduo::net::TcpConnectionPtr& conn,
	Buffer* buf,
	Timestamp receiveTime);
