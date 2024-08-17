#include "UdpNetMediator.h"
#include "UdpNet.h"
UdpNetMediator::UdpNetMediator() {
	m_pINet = new UdpNet(this);
}
UdpNetMediator::~UdpNetMediator() {
	if (m_pINet) {
		delete m_pINet;
		m_pINet = nullptr;
	}
}

//初始化网络
bool UdpNetMediator::OpenNet() {
	return m_pINet->InitNet();
}
//发送数据
bool UdpNetMediator::SendData(long lSend, char* SendBuf, int nLen) {
	return m_pINet->SendData(lSend, SendBuf, nLen);
}
//处理数据
void UdpNetMediator::DealData(long lSend, char* recvBuf, int nLen) {
    //把数据传给CKernel
    Q_EMIT SIG_ReadyData(lSend,recvBuf, nLen);
}
//关闭网络
void UdpNetMediator::CloseNet() {
	m_pINet->UnitNet();
}
