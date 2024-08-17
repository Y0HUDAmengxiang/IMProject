#pragma once
#include "INetMediator.h"
class UdpNetMediator : public INetMediator {
public:
	UdpNetMediator();
	~UdpNetMediator();
public:
	//��ʼ������
	bool OpenNet();
	//��������
	bool SendData(long lSend, char* SendBuf, int nLen);
	//��������
	void DealData(long lSend, char* recvBuf, int nLen);
	//�ر�����
	void CloseNet();
};