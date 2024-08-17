#pragma once
#include "INetMediator.h"
class TcpNetClientMediator : public INetMediator {
public:
	TcpNetClientMediator();
	~TcpNetClientMediator();
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