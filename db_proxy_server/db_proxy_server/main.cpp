/*
 * File    : db_proxy_server/main.cpp 
 *
 * Author  : Ys Li
 */

#include <list>
#include <iostream>
#include <boost/function.hpp>
#include "../muduo/net/TcpServer.h"
#include "../muduo/net/Callbacks.h"
#include "../muduo/net/InetAddress.h"
#include "../muduo/net/EventLoop.h"

#include "../base/ConfigFileReader.h"
#include "../base/ThreadPool.h"
#include "DBPool.h"
#include "CachePool.h"
//#include "other/HttpClient.h"
#include "../base/EncDec.h"
#include "model/AudioModel.h"
#include "model/MessageModel.h"
#include "model/SessionModel.h"
#include "model/RelationModel.h"
#include "model/UserModel.h"
#include "model/GroupModel.h"
#include "model/GroupMessageModel.h"
#include "model/FileModel.h"
#include "SyncCenter.h"

#include "OnMessage.h"

using std::cout;
using std::endl;


typedef muduo::net::TcpServer    TcpServer;
typedef muduo::net::EventLoop    EventLoop;
typedef muduo::net::InetAddress  InetAddress;


const unsigned int max_threads = 5;

string strAudioEnc;
std::list<EventLoop*>  g_loop_list;
std::list<TcpServer*>  g_server_list;
CThreadPool g_thread_pool;

bool db_init()
{
       //���µ�����getInstance�������Ƿ��̰߳�ȫ�ģ�
       //���Ե�һ�ε���Ӧ�������߳�����ɡ�
       //1. ��ʼ����ʼ������ģ�� 
        CacheManager* pCacheManager = CacheManager::getInstance();
	if (!pCacheManager) {
	  log("CacheManager init failed");
          return false;
	}

        //2. ��ʼ�����ݿ�ģ��
	CDBManager* pDBManager = CDBManager::getInstance();
	if (!pDBManager) {
	  log("DBManager init failed");
          return false;
	}
	cout << "db init success" << endl;

	CSyncCenter::getInstance()->init();
	CSyncCenter::getInstance()->startSync();  //ͬ��mysql��Ⱥ���lastest����ʱ�䣬����ʱ����µ�redis��.(�ú����ᴴ�������߳�)
        return true;
}


bool model_getInstance()
{
	if (!CAudioModel::getInstance()) {
		return false;
	}

	if (!CGroupMessageModel::getInstance()) {
		return false;
	}

	if (!CGroupModel::getInstance()) {
		return false;
	}

	if (!CMessageModel::getInstance()) {
		return false;
	}

	if (!CSessionModel::getInstance()) {
		return false;
	}

	if (!CRelationModel::getInstance())
	{
		return false;
	}

	if (!CUserModel::getInstance()) {
		return false;
	}

	if (!CFileModel::getInstance()) {
		return false;
	}
}


bool aes(char* str_aes_key)
{
	if (strlen(str_aes_key) != 32)
	{
		log("aes key is invalied");
		return false;
	}
	string strAesKey(str_aes_key, 32);
	CAes cAes = CAes(strAesKey);
	string strAudio = "[����]";
	char* pAudioEnc;
	uint32_t nOutLen;
	if (cAes.Encrypt(strAudio.c_str(), strAudio.length(), &pAudioEnc, nOutLen) == 0)
	{
		strAudioEnc.clear();
		strAudioEnc.append(pAudioEnc, nOutLen);
		cAes.Free(pAudioEnc);
	}
}


bool start_server(const char* server_ip, uint16_t port)
{
	InetAddress listenAddr(server_ip, port);
	EventLoop* p_loop   = new EventLoop;
	TcpServer* p_server = new TcpServer(p_loop, listenAddr, "dbProxyServer");

	//p_server->setConnectionCallback(onConnection);
	p_server->setMessageCallback(OnMessage);
        
        cout << "server start listen on:" << server_ip << ":" << port << endl;
	cout << "now enter the event loop..." << endl;
	g_loop_list.push_back(p_loop);
	g_server_list.push_back(p_server);

	p_server->start();
	p_loop->loop();
	}


void init_threadPool(unsigned int num)
{
	g_thread_pool.Init(num);
}




int main(int argc, char* argv[])
{
	signal(SIGPIPE, SIG_IGN);  //��һ���յ�Ret��fd���е�һ��д�������ں˽������ý��̷���SIGPIPE�źţ����źŵ�Ĭ����Ϊ����ֹ��ǰ���̡�
	srand(time(NULL));
	
	if (db_init() == false){   //��ʼ�����������ݿ�,����ʼͬ������
            cout << "db_init()--error" << endl;
	    return -1;
          }

	if (model_getInstance()){ //������model ��������
	   cout << "model_getInstance()--error" << endl;
           return -1;
          }

	CConfigFileReader config_file("dbproxyserver.conf");

	char* listen_ip = config_file.GetConfigName("ListenIP");
	char* str_listen_port = config_file.GetConfigName("ListenPort");
	char* str_thread_num = config_file.GetConfigName("ThreadNum");
	char* str_file_site = config_file.GetConfigName("MsfsSite");
	char* str_aes_key = config_file.GetConfigName("aesKey");

	if (!listen_ip || !str_listen_port || !str_thread_num || !str_file_site || !str_aes_key) {
		log("missing ListenIP/ListenPort/ThreadNum/MsfsSite/aesKey, exit...");
		return -1;
	}

	if (aes(str_aes_key))  //��ʼ����֤����
		return -2;
	
	uint16_t listen_port = atoi(str_listen_port);
	uint32_t thread_num = atoi(str_thread_num);

	string strFileSite(str_file_site);
	CAudioModel::getInstance()->setUrl(strFileSite);

	CStrExplode listen_ip_list(listen_ip, ';');

	for (uint32_t i = 0; i < listen_ip_list.GetItemCnt(); i++) {
			//��������������ʼ����
		start_server(listen_ip_list.GetItem(i), listen_port);		   
		}

	init_threadPool(max_threads);

	writePid();
	return 0;
}
