#include "TcpNetClient.h"

TcpNetClient::TcpNetClient(INetMediator* pMediator) :m_sock(INVALID_SOCKET), m_handle(0),m_bStop(false) {
	m_pINetMediator = pMediator;
}
TcpNetClient::~TcpNetClient() {

}

//��ʼ������:���ؿ⣬�����׽��֣����ӣ������������ݵ��߳�
bool TcpNetClient::InitNet() {
	//���ؿ�

	WSADATA wsaData;
	WORD word = MAKEWORD(2, 2);
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
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ( INVALID_SOCKET == m_sock) {
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

	sockaddr_in addrServer;
	addrServer.sin_addr.S_un.S_addr = inet_addr(DEF_IP_ADDR);
	//ת��Ϊ�����ֽ����������Ǵ�˴洢����������С�˴洢����Ҫת������
	addrServer.sin_port = htons(DEF_TCP_PORT);
	addrServer.sin_family = AF_INET;
	err = connect(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "connect error:" << WSAGetLastError() << endl;
		//�ر��׽���
		closesocket(m_sock);
		WSACleanup();
	}
	else
	{
		cout << "connect sucess" << endl;
	}
	//�������ݵ��߳�
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)this, 0, NULL);
	return true;
}
unsigned _stdcall TcpNetClient::RecvThread(void* lpVoid) {
	TcpNetClient* pThis = (TcpNetClient*)lpVoid;
	pThis->RecvData();
	return true;
}
//��������
bool TcpNetClient::SendData(long lSend, char* SendBuf, int nLen) {
	
	//1.�жϲ����Ƿ�Ϸ�
	if (!SendBuf/*sendbuf���������ݲ���Ϊ��*/ || nLen/*���ݳ���Ҳ����Ϊ0*/ <= 0) {
		cout << "TcpNetClient::SendData parameter error" << endl;
		return false;
	}
	//2.�ȷ�����С
	if (send(m_sock,(char*)&nLen,sizeof(nLen)/*nLenֻ��һ��ָ�룬�����ܴ������͵Ĵ�С*/, 0) <= 0) {
		cout << "TcpNetClient::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	//3.�ٷ�������
	if (send(m_sock, SendBuf, nLen, 0) <= 0) {
		cout << "TcpNetClient::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//��������
void TcpNetClient::RecvData() {
	
	int nRecvNum = 0;
	int PackSize = 0;
	//��¼�ۼƽ��յ���������
	int nOffSet = 0;
	while (!m_bStop) {
		//1.�Ƚ��հ��Ĵ�С
		nRecvNum = recv(m_sock, (char*)&PackSize, sizeof(int), 0);
		//���հ��Ĵ�С����������ݵĿռ�
		char* PackBuf = new char[PackSize];
		if (nRecvNum > 0) {
			//2.���հ�����
			
			while (PackSize > 0) {
				nRecvNum = recv(m_sock, PackBuf + nOffSet, PackSize, 0);
				if (nRecvNum > 0) {
					//��ӡ���ܵ�������
					nOffSet += nRecvNum;
					PackSize -= nRecvNum;
				}
				else
				{
					cout << "TcpNetClient::RecvData error:" << WSAGetLastError() << endl;
					break;
				}
			}

			//��ӡ���ܵ�����
			//cout << "TcpNetClient RecvData��" << PackBuf << endl;
			//�����ݴ��ݸ��н�����
			m_pINetMediator->DealData(m_sock, PackBuf, nOffSet);
			//�ۼƽ��ܵ�����������
			nOffSet = 0;
		}
		else
		{
			cout << "TcpNetClient::RecvData error:" << WSAGetLastError() << endl;
		}

	}

}
//�ر�����
void TcpNetClient::UnitNet() {
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