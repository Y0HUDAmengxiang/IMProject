#pragma once
//#include "INet.h"
class INet;
class INetMediator {
public:
	INetMediator(){}
	~INetMediator(){}
public:
	//������
	virtual bool OpenNet() = 0;
	//��������
	virtual bool SendData(long lSend, char* SendBuf, int nLen) = 0;
	//��������
	virtual void DealData(long lSend, char* recvBuf, int nLen) = 0;
	//�ر�����
	virtual void CloseNet() = 0;
protected:
	INet* m_pINet;
};