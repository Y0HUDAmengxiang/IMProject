#include "TcpNetServer.h"

TcpNetServer::TcpNetServer(INetMediator* pMediator):m_sock(INVALID_SOCKET),m_handle(NULL),m_bStop(false) {
	m_pINetMediator = pMediator;
}
TcpNetServer::~TcpNetServer() {
	m_pINetMediator->CloseNet();
}

//��ʼ������
bool TcpNetServer::InitNet() {
	WORD word = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(word, &wsaData);
	if (0 != err) {
		cout << " WSAStartup sucess" << endl;
	}
	else
	{
		cout << "WSAStartup error" << endl;
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
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
	//3.��ip��ַ
	sockaddr_in addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	//ת��Ϊ�����ֽ����������Ǵ�˴洢����������С�˴洢����Ҫת������
	addrServer.sin_port = htons(DEF_TCP_PORT);
	addrServer.sin_family = AF_INET;
	err = bind(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "bind error :" << WSAGetLastError() << endl;
		return false;

	}
	else
	{
		cout << "bind sucess" << endl;
	}
	//����
	err = listen(m_sock, 10);
	if (SOCKET_ERROR == err) {
		cout << "listen error" << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "listen sucess" << endl;
	}
	//����һ���������ӵ��߳�
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, (void*)this, 0, NULL);

	return true;
}
unsigned _stdcall TcpNetServer::RecvThread(void* lpVoid) {
	TcpNetServer* pThis = (TcpNetServer*)lpVoid;
	pThis->RecvData();
	return true;
}
unsigned __stdcall TcpNetServer::AcceptThread(void* lpVoid) {
	TcpNetServer* pThis = (TcpNetServer*)lpVoid;
	sockaddr_in addr;
	int addrSize = sizeof(addr);
	SOCKET sock = INVALID_SOCKET;
	HANDLE handle;
	unsigned int threadId = 0;
	/*
	* ѭ���������ӣ�ÿ�����Ӷ��Ὠ��һ���µ�socket
	*/
	
	while (!pThis->m_bStop) {
		sock = accept(pThis->m_sock, (sockaddr*)&addr, &addrSize);
		if(INVALID_SOCKET == sock){
			cout << "accpect error:" << WSAGetLastError() << endl;
			break;
		}
		else
		{
			cout << "client ip:" << inet_ntoa(addr.sin_addr) << endl;
			//ÿ�����ӳɹ����������ͻ��˴���һ���������ݵ��߳�
			handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)pThis, 0, &threadId);
			if (NULL == handle) {
				cout << "handle save fail" << endl;
			}
			//���߳̾����������
			pThis->m_listHandle.push_back(handle);
			//���̶߳�Ӧ��ID��socket��������
			pThis->m_mapThreadIdToSocket[threadId] = sock;
		}
		
	}
	return true;
}
/*
* ����Ƿ���������ģ�ÿһ�ζ�������������β���һ���µ�Ԫ��
* ��Ӧ���߳�ID�ǺͿͻ��˵�sock���Ӧ�ġ�
*/
//��������
bool TcpNetServer::SendData(long lSend, char* SendBuf, int nLen) {
	
	//1.�жϲ����Ƿ�Ϸ�
	if (!SendBuf/*sendbuf���������ݲ���Ϊ��*/ || nLen/*���ݳ���Ҳ����Ϊ0*/ <= 0) {
		cout << "TcpNetServer::SendData parameter error" << endl;
		return false;
	}
	//2.�ȷ�����С
	if (send(lSend,(char*)&nLen, sizeof(int), 0) <= 0) {
		cout << "TcpNetServer::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	//3.�ٷ�������
	if (send(lSend, SendBuf, nLen, 0) <= 0) {
		cout << "TcpNetServer::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//��������
void TcpNetServer::RecvData() {
	Sleep(50);//����һ�ᣬ��Ϊ��socket����map��Ҫһ��ʱ��
	//��ȡ��ǰ�̵߳�SOCKET
	SOCKET socket = m_mapThreadIdToSocket[GetCurrentThreadId()];
	if (!socket || INVALID_SOCKET == socket) {
		cout << "TcpNetServer::RecvData socket error" << endl;
		return;
	}
	else
	{
		cout << "TcpNetServer::RecvData socket sucess" << endl;
	}
	
	int nRecvNum = 0;
	int PackSize = 0;
	int nOffSet = 0;
	while (!m_bStop) {
		//1.�Ƚ��հ��Ĵ�С
		nRecvNum = recv(socket, (char*)&PackSize, sizeof(PackSize), 0);
		if (nRecvNum > 0) {
			//2.���հ�����
			//���հ��Ĵ�С����������ݵĿռ�
			char* PackBuf = new char[PackSize];
			while (PackSize > 0) {
				nRecvNum = recv(socket, PackBuf + nOffSet,/* ����д�ɣ�sizeof(PackBuf) ��ΪpackBuf��οռ�ʼ�մ��ڵ� */ PackSize, 0);
				if (nRecvNum > 0) {
					nOffSet += nRecvNum;
					PackSize -= nRecvNum;
				}
				else
				{
					cout << "TcpNetServer::RecvData error:" << WSAGetLastError() << endl;
					break;
				}
			}
			m_pINetMediator->DealData(socket, PackBuf, nOffSet);
			nOffSet = 0;
			
		}
		else
		{
			cout << "TcpNetServer::RecvData error:" << WSAGetLastError() << endl;
			break;
		}

	}

}
//�ر�����
void TcpNetServer::UnitNet() {
	//1.�����̣߳�1.�����̹߳�����2.�رվ����
	m_bStop = true;
	HANDLE handle;
	for (auto ite = m_listHandle.begin(); ite != m_listHandle.end();) {
		handle = *ite;
		if (handle) {
			if (WAIT_TIMEOUT == WaitForSingleObject(handle, 500)) {
				//�����ʱ��û�н����̺߳�������ǿ��ɱ���߳�
				TerminateThread(handle, -1);
			}
			CloseHandle(handle);
			m_handle == NULL;
		}
		//����Ч�ڵ��listt���Ƴ�
		ite = m_listHandle.erase(ite);
	}
	//�ر��׽���
	if (m_sock && m_sock != INVALID_SOCKET) {
		closesocket(m_sock);
	}
	WSACleanup();
}