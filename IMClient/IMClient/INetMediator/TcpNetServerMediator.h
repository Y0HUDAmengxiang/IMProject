#pragma once
#include "INetMediator.h"
class TcpNetServerMediator : public INetMediator {
public:
	TcpNetServerMediator();
	~TcpNetServerMediator();
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