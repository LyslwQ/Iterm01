#ifndef __PROXY_TASK_H__
#define __PROXY_TASK_H__

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "../muduo/net/TcpConnection.h"

#include "../base/Task.h"
#include "../base/util.h"
#include "../base/ImPduBase.h"

typedef muduo::net::TcpConnectionPtr TcpConnectionPtr;
//typedef void(*pdu_handler_t)(CImPdu* pPdu, const TcpConnectionPtr& conn);
typedef boost::function<void(CImPdu*, const TcpConnectionPtr&)> pdu_handler_t;



class CProxyTask :public CTask
{
public:
	CProxyTask(pdu_handler_t pdu_handler, CImPdu* pdu, const TcpConnectionPtr& conn);
	virtual ~CProxyTask();

	virtual void run();
private:
	const TcpConnectionPtr  m_conn;
	pdu_handler_t	  m_pdu_handler;
	CImPdu* 		  m_pPdu;   //pdu传进来后，生命期将由ProxyTask管理
};
#endif

