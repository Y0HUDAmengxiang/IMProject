#pragma once
#include "INet.h"
#include <process.h>
#include "TcpNetClientMediator.h"
class TcpNetClient : public INet {
public:
	TcpNetClient(INetMediator* pMediator);
	~TcpNetClient();
public:
	//��ʼ������
	bool InitNet();
	//��������
	bool SendData(long lSend, char* SendBuf, int nLen);
	//��������
	void RecvData();
	//�ر�����
	void UnitNet();


private:
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
	//�������ݵ��߳�
	static unsigned _stdcall RecvThread(void* lpVoid);
};