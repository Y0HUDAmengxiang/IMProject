#pragma once
#include "INet.h"
class UdpNet : public INet {
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet();
public:
	//��ʼ������
	bool InitNet();
	//��������
	bool SendData(long lSend, char* SendBuf, int nLen);
	//��������
	void RecvData();
	//�ر�����
	void UnitNet();
public:
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
private:
	static unsigned _stdcall RecvThread(void* lpVoid);

};