#pragma once
#include "INet.h"
#include <process.h>
#include <map>
#include <list>
#include "TcpNetServerMediator.h"
class TcpNetServer : public INet {
public:
	TcpNetServer(INetMediator* pMediator);
	~TcpNetServer();
public:
	//初始化网络
	bool InitNet();
	//发送数据
	bool SendData(long lSend, char* SendBuf, int nLen);
	void RecvData();
	//关闭网络
	void UnitNet();
private:
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
	//接受连接的线程
	static unsigned __stdcall AcceptThread(void* lpVoid);
	//接收数据的线程
	static unsigned _stdcall RecvThread(void* lpVoid);
	//接受连接之后:对应的ID和对应的连接账户用map保存
	map<unsigned int, SOCKET> m_mapThreadIdToSocket;
	list<HANDLE> m_listHandle;
};