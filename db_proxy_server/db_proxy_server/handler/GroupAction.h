#ifndef GROUPACTION_H_
#define GROUPACTION_H_

#include "../../base/ImPduBase.h"

#include <boost/shared_ptr.hpp>
#include "../../muduo/net/TcpConnection.h"

typedef muduo::net::TcpConnectionPtr   TcpConnectionPtr;

namespace DB_PROXY {

    void createGroup(CImPdu* pPdu, const TcpConnectionPtr& conn);
    
    void getNormalGroupList(CImPdu* pPdu, const TcpConnectionPtr& conn);
    
    void getGroupInfo(CImPdu* pPdu, const TcpConnectionPtr& conn);
    
    void modifyMember(CImPdu* pPdu, const TcpConnectionPtr& conn);
    
    void setGroupPush(CImPdu* pPdu, const TcpConnectionPtr& conn);
    
    void getGroupPush(CImPdu* pPdu, const TcpConnectionPtr& conn);

};



#endif /* GROUPACTION_H_ */
