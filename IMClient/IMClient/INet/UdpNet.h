#pragma once
#include "INet.h"
class UdpNet : public INet {
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet();
public:
	//初始化网络
	bool InitNet();
	//发送数据
	bool SendData(long lSend, char* SendBuf, int nLen);
	//接收数据
	void RecvData();
	//关闭网络
	void UnitNet();
public:
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
private:
	static unsigned _stdcall RecvThread(void* lpVoid);

};