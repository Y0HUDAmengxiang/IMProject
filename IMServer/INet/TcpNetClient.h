#pragma once
#include "INet.h"
#include <process.h>
#include "TcpNetClientMediator.h"
class TcpNetClient : public INet {
public:
	TcpNetClient(INetMediator* pMediator);
	~TcpNetClient();
public:
	//初始化网络
	bool InitNet();
	//发送数据
	bool SendData(long lSend, char* SendBuf, int nLen);
	//接收数据
	void RecvData();
	//关闭网络
	void UnitNet();


private:
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
	//接收数据的线程
	static unsigned _stdcall RecvThread(void* lpVoid);
};