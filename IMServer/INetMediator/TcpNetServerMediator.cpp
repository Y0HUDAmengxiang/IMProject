#include "TcpNetServerMediator.h"
#include "TcpNetServer.h"
#include "../CKernel.h"


TcpNetServerMediator::TcpNetServerMediator() {
	m_pINet = new TcpNetServer(this);
}
TcpNetServerMediator::~TcpNetServerMediator() {
	if (m_pINet) {
		delete m_pINet;
		m_pINet = NULL;
	}
}

//初始化网络
bool TcpNetServerMediator::OpenNet() {
	return m_pINet->InitNet();
}
//发送数据
bool TcpNetServerMediator::SendData(long lSend, char* SendBuf, int nLen) {
	return m_pINet->SendData(lSend, SendBuf, nLen);
}
//接收数据
void TcpNetServerMediator::DealData(long lSend, char* recvBuf, int nLen) {

	CKernel::pKernel->ReadyData(lSend, recvBuf, nLen);
	
	
}
//关闭网络
void TcpNetServerMediator::CloseNet() {
	m_pINet->UnitNet();
}