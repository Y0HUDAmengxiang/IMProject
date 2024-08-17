#pragma once
#include <QObject>
//#include "INet.h"
class INet;
class INetMediator:public QObject {
    Q_OBJECT
public:
    INetMediator();
    ~INetMediator();
public:
	//打开网络
	virtual bool OpenNet() = 0;
	//发送数据
	virtual bool SendData(long lSend, char* SendBuf, int nLen) = 0;
	//接收数据
	virtual void DealData(long lSend, char* recvBuf, int nLen) = 0;
	//关闭网络
	virtual void CloseNet() = 0;
protected:
	INet* m_pINet;
signals:
    void SIG_ReadyData(long lSend,char* recvBuf,int nLen);
};
