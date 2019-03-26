#include "ProxyTask.h"


CProxyTask::CProxyTask(pdu_handler_t pdu_handler, CImPdu* pdu, const TcpConnectionPtr& conn)
	:m_pdu_handler(pdu_handler),
	 m_pPdu(pdu),
	 m_conn(conn) {}

CProxyTask::~CProxyTask()
{
	if (m_pPdu) {
		delete m_pPdu;
	}
}

void CProxyTask::run()
{

	if (!m_pPdu) {
		// tell CProxyConn to close connection with m_conn_uuid
		m_conn->forceClose();
	}
	else {
		if (m_pdu_handler) {
			m_pdu_handler(m_pPdu, m_conn);
		}
	}
}
