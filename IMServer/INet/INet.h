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
	//��ʼ������
	virtual bool InitNet() = 0;
	//��������
	virtual bool SendData(long lSend, char* SendBuf, int nLen) = 0;
	//��������
	virtual void RecvData() = 0;
	//�ر�����
	virtual void UnitNet() = 0;
protected:
	INetMediator* m_pINetMediator;
};