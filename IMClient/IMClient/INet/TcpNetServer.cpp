#include "TcpNetServer.h"

TcpNetServer::TcpNetServer(INetMediator* pMediator):m_sock(INVALID_SOCKET),m_handle(NULL),m_bStop(false) {
	m_pINetMediator = pMediator;
}
TcpNetServer::~TcpNetServer() {
	m_pINetMediator->CloseNet();
}

//初始化网络
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
	//3.绑定ip地址
	sockaddr_in addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	//转换为本机字节序，网络中是大端存储，电脑中是小端存储，需要转化过来
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
	//监听
	err = listen(m_sock, 10);
	if (SOCKET_ERROR == err) {
		cout << "listen error" << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "listen sucess" << endl;
	}
	//创建一个接收连接的线程
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
	* 循环接受连接，每次连接都会建立一个新的socket
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
			//每次连接成功都会给这个客户端创建一个接收数据的线程
			handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)pThis, 0, &threadId);
			if (NULL == handle) {
				cout << "handle save fail" << endl;
			}
			//把线程句柄保存起来
			pThis->m_listHandle.push_back(handle);
			//把线程对应的ID和socket保存起来
			pThis->m_mapThreadIdToSocket[threadId] = sock;
		}
		
	}
	return true;
}
/*
* 句柄是放在链表里的，每一次都会重新在链表尾添加一个新的元素
* 对应的线程ID是和客户端的sock相对应的。
*/
//发送数据
bool TcpNetServer::SendData(long lSend, char* SendBuf, int nLen) {
	
	//1.判断参数是否合法
	if (!SendBuf/*sendbuf传来的数据不能为空*/ || nLen/*数据长度也不能为0*/ <= 0) {
		cout << "TcpNetServer::SendData parameter error" << endl;
		return false;
	}
	//2.先发包大小
	if (send(lSend,(char*)&nLen, sizeof(int), 0) <= 0) {
		cout << "TcpNetServer::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	//3.再发包内容
	if (send(lSend, SendBuf, nLen, 0) <= 0) {
		cout << "TcpNetServer::SendData parameter error" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//接收数据
void TcpNetServer::RecvData() {
	Sleep(50);//休眠一会，因为把socket存入map需要一点时间
	//获取当前线程的SOCKET
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
		//1.先接收包的大小
		nRecvNum = recv(socket, (char*)&PackSize, sizeof(PackSize), 0);
		if (nRecvNum > 0) {
			//2.接收包内容
			//按照包的大小申请接受数据的空间
			char* PackBuf = new char[PackSize];
			while (PackSize > 0) {
				nRecvNum = recv(socket, PackBuf + nOffSet,/* 不可写成：sizeof(PackBuf) 因为packBuf这段空间始终存在的 */ PackSize, 0);
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
//关闭网络
void TcpNetServer::UnitNet() {
	//1.回收线程（1.结束线程工作，2.关闭句柄）
	m_bStop = true;
	HANDLE handle;
	for (auto ite = m_listHandle.begin(); ite != m_listHandle.end();) {
		handle = *ite;
		if (handle) {
			if (WAIT_TIMEOUT == WaitForSingleObject(handle, 500)) {
				//如果超时还没有结束线程函数，再强制杀死线程
				TerminateThread(handle, -1);
			}
			CloseHandle(handle);
			m_handle == NULL;
		}
		//把无效节点从listt中移除
		ite = m_listHandle.erase(ite);
	}
	//关闭套接字
	if (m_sock && m_sock != INVALID_SOCKET) {
		closesocket(m_sock);
	}
	WSACleanup();
}