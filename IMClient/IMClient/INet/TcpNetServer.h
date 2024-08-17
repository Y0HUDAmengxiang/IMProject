#pragma once
#include "INet.h"
#include <process.h>
#include <map>
#include <list>
#include "TcpNetServerMediator.h"
class TcpNetServer : public INet {
public:
	TcpNetServer(INetMediator* pMediator);
	~TcpNetServer();
public:
	//��ʼ������
	bool InitNet();
	//��������
	bool SendData(long lSend, char* SendBuf, int nLen);
	void RecvData();
	//�ر�����
	void UnitNet();
private:
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
	//�������ӵ��߳�
	static unsigned __stdcall AcceptThread(void* lpVoid);
	//�������ݵ��߳�
	static unsigned _stdcall RecvThread(void* lpVoid);
	//��������֮��:��Ӧ��ID�Ͷ�Ӧ�������˻���map����
	map<unsigned int, SOCKET> m_mapThreadIdToSocket;
	list<HANDLE> m_listHandle;
};