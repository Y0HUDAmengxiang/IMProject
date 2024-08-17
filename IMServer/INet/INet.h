#pragma once
#include <iostream>
#include <WinSock2.h>
#include "config.h"
using namespace std;
#pragma comment(lib,"ws2_32.lib")

class INetMediator;
class INet {
public:
	INet(){}
	~INet(){}
public:
	//初始化网络
	virtual bool InitNet() = 0;
	//发送数据
	virtual bool SendData(long lSend, char* SendBuf, int nLen) = 0;
	//接收数据
	virtual void RecvData() = 0;
	//关闭网络
	virtual void UnitNet() = 0;
protected:
	INetMediator* m_pINetMediator;
};