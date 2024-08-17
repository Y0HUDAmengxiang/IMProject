#pragma once
#include "INetMediator.h"
class UdpNetMediator : public INetMediator {
    Q_OBJECT
public:
	UdpNetMediator();
	~UdpNetMediator();
public:
	//初始化网络
	bool OpenNet();
	//发送数据
	bool SendData(long lSend, char* SendBuf, int nLen);
	//接收数据
	void DealData(long lSend, char* recvBuf, int nLen);
	//关闭网络
	void CloseNet();

};
