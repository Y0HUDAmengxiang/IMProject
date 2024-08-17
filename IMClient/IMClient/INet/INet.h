#pragma once
#include <iostream>
#include <WinSock2.h>
#include "config.h"
#include <set>
using namespace std;
//#pragma comment(lib,"ws2_32.lib")

class INetMediator;
class INet {
public:
	INet(){}
	~INet(){}
public:
	//初始化网络
	virtual bool InitNet() = 0;
	//发送数据
	virtual bool SendData(long lSend, char* SendBuf, int nLen) = 0;
	//接收数据
	virtual void RecvData() = 0;
	//关闭网络
	virtual void UnitNet() = 0;
    static set<long> GetipList()
    {
        set<long> ipList;
        char name[100] ="";
        //先获取主机名子
       gethostname(name,sizeof(name));
        //在根据主机上名字列表取ip列表
        struct hostent *remoteHost = gethostbyname(name);
        int i=0;
        long ip=0;
        while(remoteHost->h_addr_list[i] !=0 ){
            ip = *(u_long *) remoteHost->h_addr_list[i++];
            ipList.insert(ip);
        }
        return ipList;

    }

protected:
	INetMediator* m_pINetMediator;
};
