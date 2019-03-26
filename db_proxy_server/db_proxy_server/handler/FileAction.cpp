#include "FileAction.h"
#include "../model/FileModel.h"
#include "../../base/pb/protocol/IM.File.pb.h"

#include "../../base/util.h"



namespace DB_PROXY {

    
    void hasOfflineFile(CImPdu* pPdu, const TcpConnectionPtr& conn)
    {
        IM::File::IMFileHasOfflineReq msg;
        IM::File::IMFileHasOfflineRsp msgResp;
        if(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()))
        {
            CImPdu* pPduRes = new CImPdu;
            
            uint32_t nUserId = msg.user_id();
            CFileModel* pModel = CFileModel::getInstance();
            list<IM::BaseDefine::OfflineFileInfo> lsOffline;
            pModel->getOfflineFile(nUserId, lsOffline);
            msgResp.set_user_id(nUserId);
            for (list<IM::BaseDefine::OfflineFileInfo>::iterator it=lsOffline.begin();
                 it != lsOffline.end(); ++it) {
                IM::BaseDefine::OfflineFileInfo* pInfo = msgResp.add_offline_file_list();
    //            *pInfo = *it;
                pInfo->set_from_user_id(it->from_user_id());
                pInfo->set_task_id(it->task_id());
                pInfo->set_file_name(it->file_name());
                pInfo->set_file_size(it->file_size());
            }
            
            log("userId=%u, count=%u", nUserId, msgResp.offline_file_list_size());
            
            msgResp.set_attach_data(msg.attach_data());
            pPduRes->SetPBMsg(&msgResp);
            pPduRes->SetSeqNum(pPdu->GetSeqNum());
            pPduRes->SetServiceId(IM::BaseDefine::SID_FILE);
            pPduRes->SetCommandId(IM::BaseDefine::CID_FILE_HAS_OFFLINE_RES);
            //CProxyConn::AddResponsePdu(conn_uuid, pPduRes);
			conn->send(pPduRes->GetBuffer(), pPduRes->GetLength());  //数据最终会在conn.Buddy所在的io线程中发送出去。

        }
        else
        {
            log("parse pb failed");
        }
    }
    
    void addOfflineFile(CImPdu* pPdu, const TcpConnectionPtr& conn)
    {
        IM::File::IMFileAddOfflineReq msg;
        if(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()))
        {
            uint32_t nUserId = msg.from_user_id();
            uint32_t nToId = msg.to_user_id();
            string strTaskId = msg.task_id();
            string strFileName = msg.file_name();
            uint32_t nFileSize = msg.file_size();
            CFileModel* pModel = CFileModel::getInstance();
            pModel->addOfflineFile(nUserId, nToId, strTaskId, strFileName, nFileSize);
            log("fromId=%u, toId=%u, taskId=%s, fileName=%s, fileSize=%u", nUserId, nToId, strTaskId.c_str(), strFileName.c_str(), nFileSize);
        }
    }
    
    void delOfflineFile(CImPdu* pPdu, const TcpConnectionPtr& conn)
    {
        IM::File::IMFileDelOfflineReq msg;
        if(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()))
        {
            uint32_t nUserId = msg.from_user_id();
            uint32_t nToId = msg.to_user_id();
            string strTaskId = msg.task_id();
            CFileModel* pModel = CFileModel::getInstance();
            pModel->delOfflineFile(nUserId, nToId, strTaskId);
            log("fromId=%u, toId=%u, taskId=%s", nUserId, nToId, strTaskId.c_str());
        }
    }
};
