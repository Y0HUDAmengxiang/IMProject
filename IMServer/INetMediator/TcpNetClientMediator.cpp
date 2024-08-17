#include "TcpNetClientMediator.h"
#include "TcpNetClient.h"
TcpNetClientMediator::TcpNetClientMediator() {
	m_pINet = new TcpNetClient(this);
}
TcpNetClientMediator::~TcpNetClientMediator() {
	if (m_pINet) {
		delete m_pINet;
		m_pINet = NULL;
	}
}

//初始化网络
bool TcpNetClientMediator::OpenNet() {
	return m_pINet->InitNet();
}
//发送数据
bool TcpNetClientMediator::SendData(long lSend, char* SendBuf, int nLen) {
	//cout << "TcpNetClientMediator::SendData" << SendBuf << endl;
	return m_pINet->SendData(lSend, SendBuf, nLen);
}
//接收数据
void TcpNetClientMediator::DealData(long lSend, char* recvBuf, int nLen) {
	cout << "TcpNetClientMediator::DealData" << recvBuf << endl;
}
//关闭网络
void TcpNetClientMediator::CloseNet() {
	m_pINet->UnitNet();
}