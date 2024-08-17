#pragma once
#include "INetMediator.h"
#include "CMySql.h"
#include "config.h"
#include <map>

using namespace std;
//定义列的成员函数指针
class CKernel;
typedef void (CKernel ::* PFUN)(long lSend, char* recvBuf, int nLen);
class CKernel {
public:
	static CKernel* pKernel;
	CKernel();
	~CKernel();
public:
	//初始化函数指针:
	void setFunMap();
	//打开服务器
	bool startServer();
	//关闭服务器
	void CloseServer();
	//处理所有收到的数据
	void ReadyData(long lSend, char* recvBuf, int nLen);
	//处理注册请求
	void dealRegisterRq(long lSend, char* recvBuf, int nLen);
	//处理登录请求
	void dealLoginRq(long lSend, char* recvBuf, int nLen);
	//获取好友的信息列表（包括自己）
	void getFriendInfoList(int userId);
	//根据id查信息
	void getUserInfoById(int id,_STRU_TCP_FRIEND_INFO_RQ* info);
	//处理聊天请求
	void dealChatRq(long lSend, char* recvBuf, int nLen);
	//处理下线请求
	void dealOfflineRq(long lSend, char* recvBuf, int nLen);
	//处理加好友请求
	void dealAddFriendRq(long lSend, char* recvBuf, int nLen);
	//处理添加好友回复
	void dealAddFriendRs(long lSend, char* recvBuf, int nLen);
	PFUN m_funMap[_DEF_PROTOCOL_CONT];
	//定义id和SOCKET的map用于保存
	map<int, SOCKET>m_mapidToSocket;
private:
	INetMediator* m_pMediator;
	CMySql m_Sql;
	

};

