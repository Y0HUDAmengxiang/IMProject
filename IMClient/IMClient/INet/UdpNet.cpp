#include "UdpNet.h"
#include "UdpNetMediator.h"
#include <process.h>
#include <QDebug>
UdpNet::UdpNet(INetMediator* pMediator):m_sock(INVALID_SOCKET),m_handle(0),m_bStop(false) {
	m_pINetMediator = pMediator;
}
UdpNet::~UdpNet() {
	UnitNet();
}

//初始化网络
bool UdpNet::InitNet() {
	//加载库
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
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sock == INVALID_SOCKET) {
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
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	//转换为本机字节序，网络中是大端存储，电脑中是小端存储，需要转化过来
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
	//申请广播权限
	bool val = true;
	setsockopt(m_sock,SOL_SOCKET, SO_BROADCAST, (char*)&val, sizeof(val));
	//创建一个接受数据的线程
	/*为什么不用CreatThread？*/
	/*
	* CreateThread和ExitThread是一对
	* 如果使用CreateThread的话，退出线程的时候自动调用ExitThread，如果在线程中使用了C++运行时库的函数（例如strcpy），
	* 这个函数会申请空间，并且不会回收，EXitThread也不会回收空间造成空间浪费
	* _beginthreadex 和 _endthreadex 是一对，_endthreadex会先回收空间，然后再调用ExitThrea。
	*/
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)this, 0, NULL);
	if (NULL == m_handle) {
		cout << "handle fail" << endl;

		//关闭套接字
		closesocket(m_sock);
		//卸载库
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
//发送数据
bool UdpNet::SendData(long lSend, char* SendBuf, int nLen) {
	sockaddr_in sockAddr_Client;
	sockAddr_Client.sin_family = AF_INET;
	sockAddr_Client.sin_port = htons(DEF_UDP_PORT);
	sockAddr_Client.sin_addr.S_un.S_addr = lSend;
    if (sendto(m_sock, SendBuf, nLen, 0, (sockaddr*)&sockAddr_Client, sizeof(sockAddr_Client)) >= 0) {
        qDebug()<< "UdpNet::SendData" << SendBuf;
        return true;
    }
	else
	{
        qDebug() << "UdpNet::SendData error:";
		//关闭套接字
		closesocket(m_sock);
		//卸载库
		WSACleanup();
	}
	return false;
}
	

//接收数据
void UdpNet::RecvData() {
	sockaddr_in sockAddrFromClient;
	int sockAddrSize = sizeof(sockAddrFromClient);
	char recvBuf[4096] = "";
	int nRecvNum = 0;
	while (!m_bStop) {
		nRecvNum = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&sockAddrFromClient, &sockAddrSize);
		if (nRecvNum > 0) {
			m_pINetMediator->DealData(sockAddrFromClient.sin_addr.S_un.S_addr, recvBuf, sockAddrSize);
			cout << "接受数据成功" << recvBuf << endl;
		}
		else
		{
			cout << "UdpNet::RecvData error: " << WSAGetLastError() << endl;
			break;
		}
	}
}
//关闭网络
void UdpNet::UnitNet() {
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
