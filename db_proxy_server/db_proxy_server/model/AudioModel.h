/*
 * File    : db_proxy_server/main.cpp
 *
 * Author  : Ys Li
 */

#ifndef AUDIO_MODEL_H_
#define AUDIO_MODEL_H_


#include <list>
#include <map>
#include "../../base/public_define.h"
#include "../../base/util.h"
#include "../../base/pb/protocol/IM.BaseDefine.pb.h"

using namespace std;


class CAudioModel {
public:
	virtual ~CAudioModel();

	static CAudioModel* getInstance();
	void setUrl(string& strFileUrl);

	bool readAudios(list<IM::BaseDefine::MsgInfo>& lsMsg);

	int saveAudioInfo(uint32_t nFromId, uint32_t nToId, uint32_t nCreateTime, const char* pAudioData, uint32_t nAudioLen);

private:
	CAudioModel();
	//    void GetAudiosInfo(uint32_t nAudioId, IM::BaseDefine::MsgInfo& msg);
	bool readAudioContent(uint32_t nCostTime, uint32_t nSize, const string& strPath, IM::BaseDefine::MsgInfo& msg);

private:
	static CAudioModel*	m_pInstance;
	string m_strFileSite;
};



#endif /* AUDIO_MODEL_H_ */
