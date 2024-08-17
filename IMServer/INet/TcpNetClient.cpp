#include "TcpNetClient.h"

TcpNetClient::TcpNetClient(INetMediator* pMediator) :m_sock(INVALID_SOCKET), m_handle(0),m_bStop(false) {
	m_pINetMediator = pMediator;
}
TcpNetClient::~TcpNetClient() {

}

//初始化网络:加载库，创建套接字，连接，创建接收数据的线程
bool TcpNetClient::InitNet() {
	//加载库

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
	//判断库是不是2.2版本
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion) != 2) {
		cout << "version fail:" << WSAGetLastError() << endl;
		//卸载库
		WSACleanup();
		return false;
	}
	else
	{
		cout << "version sucess" << endl;
	}
	//创建套接字
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ( INVALID_SOCKET == m_sock) {
		cout << "sock error:" << WSAGetLastError() << endl;
		//卸载库
		WSACleanup();
		//关闭套接字
		closesocket(m_sock);
		return false;
	}
	else
	{
		cout << "sock secess" << endl;
	}

	sockaddr_in addrServer;
	addrServer.sin_addr.S_un.S_addr = inet_addr(DEF_IP_ADDR);
	//转换为本机字节序，网络中是大端存储，电脑中是小端存储，需要转化过来
	addrServer.sin_port = htons(DEF_TCP_PORT);
	addrServer.sin_family = AF_INET;
	err = connect(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "connect error:" << WSAGetLastError() << endl;
		//关闭套接字
		closesocket(m_sock);
		WSACleanup();
	}
	else
	{
		cout << "connect sucess" << endl;
	}
	//接收数据的线程
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)this, 0, NULL);
	return true;
}
unsigned _stdcall TcpNetClient::RecvThread(void* lpVoid) {
	TcpNetClient* pThis = (TcpNetClient*)lpVoid;
	pThis->RecvData();
	return true;
}
//发送数据
bool TcpNetClient::SendData(long lSend, char* SendBuf, int nLen) {
	
	//1.判断参数是否合法
	if (!SendBuf/*sendbuf传来的数据不能为空*/ || nLen/*数据长度也不能为0*/ <= 0) {
		cout << "TcpNetClient::SendData parameter error" << endl;
		return false;
	}
	//2.先发包大小
	if (send(m_sock,(char*)&nLen,sizeof(nLen)/*nLen只是一个指针，并不能代表类型的大小*/, 0) <= 0) {
		cout << "TcpNetClient::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	//3.再发包内容
	if (send(m_sock, SendBuf, nLen, 0) <= 0) {
		cout << "TcpNetClient::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//接收数据
void TcpNetClient::RecvData() {
	
	int nRecvNum = 0;
	int PackSize = 0;
	//记录累计接收到的数据量
	int nOffSet = 0;
	while (!m_bStop) {
		//1.先接收包的大小
		nRecvNum = recv(m_sock, (char*)&PackSize, sizeof(int), 0);
		//按照包的大小申请接受数据的空间
		char* PackBuf = new char[PackSize];
		if (nRecvNum > 0) {
			//2.接收包内容
			
			while (PackSize > 0) {
				nRecvNum = recv(m_sock, PackBuf + nOffSet, PackSize, 0);
				if (nRecvNum > 0) {
					//打印接受到的数据
					nOffSet += nRecvNum;
					PackSize -= nRecvNum;
				}
				else
				{
					cout << "TcpNetClient::RecvData error:" << WSAGetLastError() << endl;
					break;
				}
			}

			//打印接受的数据
			//cout << "TcpNetClient RecvData：" << PackBuf << endl;
			//把数据传递给中介者类
			m_pINetMediator->DealData(m_sock, PackBuf, nOffSet);
			//累计接受的数据量清零
			nOffSet = 0;
		}
		else
		{
			cout << "TcpNetClient::RecvData error:" << WSAGetLastError() << endl;
		}

	}

}
//关闭网络
void TcpNetClient::UnitNet() {
	//1.回收线程（1.结束线程工作，2.关闭句柄）
	m_bStop = true;
	if (m_handle) {
		if (WAIT_TIMEOUT == WaitForSingleObject(m_handle, 500)) {
			//如果超时还没有结束线程函数，再强制杀死线程
			TerminateThread(m_handle, -1);
		}
		CloseHandle(m_handle);
		m_handle == NULL;
	}
	closesocket(m_sock);
	WSACleanup();
}