# *IM项目精解

**udp部分：**

## 1.初始化网络（InitNet）：

#### **（1）加载库**

```c++
WORD word = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(word, &wsaData);
	if (err != 0) {
		cout << "创建库失败:" << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "创建库成功" << endl;
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
```

这段代码中**WORD**类型的参数是一个输入参数，在调用MAKEWORD的时候需要带着值进去，其中MAKEWORD的参数就是版本号。

**WSADATA**类型的参数是一个输出参数，就不需要复制。

**WSAStartup**函数会返回一个int值的参数，所以需要用一个定义一个int型的参数来接住。

**（2）创建套接字**

```c++
m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_sock) {
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
```

我们在判断一个常量和变量的时候需要把常量放在前边，因为在写项目的时候 **等于** 条件经常会少写一个等于号，这时，若常量在等号左侧的时候，就会报一个编译错误，因为无法将一个变量赋值给常量。

**（3）绑定IP地址**

```c++
sockaddr_in addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
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
//申请一个广播权限
	bool val = true;
	setsockopt(m_sock,SOL_SOCKET, SO_BROADCAST, (char*)&val, sizeof(val));
```

​	转换为本机字节序，网络中是大端存储，电脑中是小端存储，需要用 **htons**转化过来

绑定ip地址需要用**bind()**函数

**（4）创建一个接收数据的线程**

为什么用  **_beginthreadex** 而不用 **CreatThread**？

CreateThread和ExitThread是一对，如果使用CreateThread的话，退出线程的时候自动调用ExitThread，如果在线程中使用了C++运行时库的函数（例如strcpy），这个函数会申请空间，并且不会回收，EXitThread也不会回收空间造成空间浪费，_beginthreadex 和 _endthreadex 是一对，_endthreadex会先回收空间，然后再调用ExitThread。

**_beginthreadex**

### 参数

*`start_address`*
启动开始执行新线程的例程的地址。 对于 **`_beginthread`**，调用约定要么 [`__cdecl`](https://learn.microsoft.com/zh-cn/cpp/cpp/cdecl?view=msvc-170) 是本机代码) (， [`__clrcall`](https://learn.microsoft.com/zh-cn/cpp/cpp/clrcall?view=msvc-170) 要么是托管代码) (。 对于 **`_beginthreadex`**，调用约定要么 [`__stdcall`](https://learn.microsoft.com/zh-cn/cpp/cpp/stdcall?view=msvc-170) 是本机代码) (， [`__clrcall`](https://learn.microsoft.com/zh-cn/cpp/cpp/clrcall?view=msvc-170) 要么是托管代码) (。

*`stack_size`*
新线程的堆栈大小或 0。

*`arglist`*
要传递到新线程的参数列表或 `NULL`。

*`Security`*
指向 [`SECURITY_ATTRIBUTES`](https://learn.microsoft.com/zh-cn/previous-versions/windows/desktop/legacy/aa379560(v=vs.85)) 结构的指针，此结构确定返回的句柄是否由子进程继承。 如果 *`Security`* 为 `NULL`，则无法继承句柄。

*`initflag`*
控制新线程的初始状态的标志。 将 *`initflag`* 设置为 0 以立即运行，或设置为 `CREATE_SUSPENDED` 以在挂起状态下创建线程；使用 [`ResumeThread`](https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-resumethread) 来执行此线程。 设置为 *`initflag`*`STACK_SIZE_PARAM_IS_A_RESERVATION` 标志以用作 *`stack_size`* 堆栈的初始保留大小（以字节为单位）;如果未指定此标志， *`stack_size`* 则指定提交大小。

*`thrdaddr`*
指向接收线程标识符的 32 位变量。 如果是 `NULL`，则不使用它。

### 参数：

```c++
uintptr_t _beginthreadex( // NATIVE CODE
   void *security,//线程的安全级别
   unsigned stack_size,//线程堆栈初始大小，初始大小默认是1M
   unsigned ( __stdcall *start_address )( void * ),//线程的起始地址，函数名也就是起始地址。
   void *arglist,//线程函数的参数列表
   unsigned initflag,//线程的状态
   unsigned *thrdaddr//操作系统给线程分配的id
);
```

*`start_address`*
启动开始执行新线程的例程的地址。 对于 **`_beginthread`**，调用约定要么 [`__cdecl`](https://learn.microsoft.com/zh-cn/cpp/cpp/cdecl?view=msvc-170) 是本机代码) (， [`__clrcall`](https://learn.microsoft.com/zh-cn/cpp/cpp/clrcall?view=msvc-170) 要么是托管代码) (。 对于 **`_beginthreadex`**，调用约定要么 [`__stdcall`](https://learn.microsoft.com/zh-cn/cpp/cpp/stdcall?view=msvc-170) 是本机代码) (， [`__clrcall`](https://learn.microsoft.com/zh-cn/cpp/cpp/clrcall?view=msvc-170) 要么是托管代码) (。

*`stack_size`*
新线程的堆栈大小或 0。

*`arglist`*
要传递到新线程的参数列表或 `NULL`。

*`Security`*
指向 [`SECURITY_ATTRIBUTES`](https://learn.microsoft.com/zh-cn/previous-versions/windows/desktop/legacy/aa379560(v=vs.85)) 结构的指针，此结构确定返回的句柄是否由子进程继承。 如果 *`Security`* 为 `NULL`，则无法继承句柄。

*`initflag`*
控制新线程的初始状态的标志。 将 *`initflag`* 设置为 0 以立即运行，或设置为 `CREATE_SUSPENDED` 以在挂起状态下创建线程；使用 [`ResumeThread`](https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-resumethread) 来执行此线程。 设置为 *`initflag`*`STACK_SIZE_PARAM_IS_A_RESERVATION` 标志以用作 *`stack_size`* 堆栈的初始保留大小（以字节为单位）;如果未指定此标志， *`stack_size`* 则指定提交大小。

*`thrdaddr`*
指向接收线程标识符的 32 位变量。 如果是 `NULL`，则不使用它。

### 返回值：

![image-20230721140003978](C:\Users\fanyuhang\AppData\Roaming\Typora\typora-user-images\image-20230721140003978.png)

可以看到**HANDLE**是由void* 重新typedef出来的一个类型，void*兼容任何类型所以可以强转。

```C++
unsigned _stdcall UdpNet::RecvThread(void* lpVoid) {
	UdpNet* pThis = (UdpNet*)lpVoid;
	pThis->RecvData();
	return true;
}
```

## 2.发送/接收数据SendData/RecvData(long lSend, char* SendBuf, int nLen)：

```c++
bool UdpNet::SendData(long lSend, char* SendBuf, int nLen) {
	sockaddr_in sockAddr_Client;
	sockAddr_Client.sin_family = AF_INET;
	sockAddr_Client.sin_port = htons(DEF_UDP_PORT);
	sockAddr_Client.sin_addr.S_un.S_addr = lSend;
	if (sendto(m_sock, SendBuf, nLen, 0, (sockaddr*)&sockAddr_Client, sizeof(sockAddr_Client)) >= 0) {

		return true;
	}
	else
	{
		cout << "UdpNet::SendData error:" << WSAGetLastError() << endl;
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
	char recvBuf[1024] = "";
	int nRecvNum = 0;
	while (!m_bStop) {
		nRecvNum = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&sockAddrFromClient, &sockAddrSize);
		if (nRecvNum > 0) {
			cout << "接受数据成功" << recvBuf << endl;
		}
		else
		{
			cout << "UdpNet::RecvData error: " << WSAGetLastError() << endl;
			break;
		}
	}
}
```

## 3.关闭网络UnInit()

```C++
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
```

## TCP:

### 1.初始化网络

```c++
bool TcpNetClient::InitNet() {
	//加载库
	WORD word = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(word, &wsaData);
	if (err != 0) {
		cout << "创建库失败:" << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "创建库成功" << endl;
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
```

与udp大差不差。





