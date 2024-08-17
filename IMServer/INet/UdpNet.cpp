#include "UdpNet.h"
#include "UdpNetMediator.h"
#include <process.h>
UdpNet::UdpNet(INetMediator* pMediator):m_sock(INVALID_SOCKET),m_handle(0),m_bStop(false) {
	m_pINetMediator = pMediator;
}
UdpNet::~UdpNet() {
	UnitNet();
}

//��ʼ������
bool UdpNet::InitNet() {
	//���ؿ�
	WORD word = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(word, &wsaData);
	if (err != 0) {
		cout << "WSAStartup error:" << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "WSAStartup sucess" << endl;
	}
	//�жϿ��ǲ���2.2�汾
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion) != 2) {
		cout << "version fail:" << WSAGetLastError() << endl;
		//ж�ؿ�
		WSACleanup();
		return false;
	}
	else
	{
		cout << "version sucess" << endl;
	}
	//�����׽���
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sock == INVALID_SOCKET) {
		cout << "sock error:" << WSAGetLastError() << endl;
		//ж�ؿ�
		WSACleanup();
		//�ر��׽���
		closesocket(m_sock);
		return false;
	}
	else
	{
		cout << "sock secess" << endl;
	}
	//��ip��ַ
	sockaddr_in addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	//ת��Ϊ�����ֽ����������Ǵ�˴洢����������С�˴洢����Ҫת������
	addrServer.sin_port = htons(DEF_UDP_PORT);
	addrServer.sin_family = AF_INET;
	err = bind(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "bind error :" << WSAGetLastError() << endl;
		
	}
	else
	{
		cout << "bind sucess" << endl;
	}
	//����㲥Ȩ��
	bool val = true;
	setsockopt(m_sock,SOL_SOCKET, SO_BROADCAST, (char*)&val, sizeof(val));
	//����һ���������ݵ��߳�
	/*Ϊʲô����CreatThread��*/
	/*
	* CreateThread��ExitThread��һ��
	* ���ʹ��CreateThread�Ļ����˳��̵߳�ʱ���Զ�����ExitThread��������߳���ʹ����C++����ʱ��ĺ���������strcpy����
	* �������������ռ䣬���Ҳ�����գ�EXitThreadҲ������տռ���ɿռ��˷�
	* _beginthreadex �� _endthreadex ��һ�ԣ�_endthreadex���Ȼ��տռ䣬Ȼ���ٵ���ExitThrea��
	*/
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)this, 0, NULL);
	if (NULL == m_handle) {
		cout << "handle fail" << endl;

		//�ر��׽���
		closesocket(m_sock);
		//ж�ؿ�
		WSACleanup();
		return false;
	}
	else
	{
		cout << "handle sucess" << endl;
	}
	return true;
}
unsigned _stdcall UdpNet::RecvThread(void* lpVoid) {
	UdpNet* pThis = (UdpNet*)lpVoid;
	pThis->RecvData();
	return true;
}
//��������
bool UdpNet::SendData(long lSend, char* SendBuf, int nLen) {
	sockaddr_in sockAddr_Client;
	sockAddr_Client.sin_family = AF_INET;
	sockAddr_Client.sin_port = htons(DEF_UDP_PORT);
	sockAddr_Client.sin_addr.S_un.S_addr = lSend;
	if (sendto(m_sock, SendBuf, nLen, 0, (sockaddr*)&sockAddr_Client, sizeof(sockAddr_Client)) >= 0) {
		cout << "UdpNet::SendData" << SendBuf << "�������" << endl;
		return true;
	}
	else
	{
		cout << "UdpNet::SendData error:" << WSAGetLastError() << endl;
		//�ر��׽���
		closesocket(m_sock);
		//ж�ؿ�
		WSACleanup();
	}
	return false;
}
	

//��������
void UdpNet::RecvData() {
	sockaddr_in sockAddrFromClient;
	int sockAddrSize = sizeof(sockAddrFromClient);
	char recvBuf[4096] = "";
	int nRecvNum = 0;
	while (!m_bStop) {
		nRecvNum = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&sockAddrFromClient, &sockAddrSize);
		if (nRecvNum > 0) {
			m_pINetMediator->DealData(sockAddrFromClient.sin_addr.S_un.S_addr, recvBuf, sockAddrSize);
			cout << "�������ݳɹ�" << recvBuf << endl;
		}
		else
		{
			cout << "UdpNet::RecvData error: " << WSAGetLastError() << endl;
			break;
		}
	}
}
//�ر�����
void UdpNet::UnitNet() {
	//1.�����̣߳�1.�����̹߳�����2.�رվ����
	m_bStop = true;
	if (m_handle) {
		if (WAIT_TIMEOUT == WaitForSingleObject(m_handle, 500)) {
			//�����ʱ��û�н����̺߳�������ǿ��ɱ���߳�
			TerminateThread(m_handle, -1);
		}
		CloseHandle(m_handle);
		m_handle == NULL;
	}
	closesocket(m_sock);
	WSACleanup();
}