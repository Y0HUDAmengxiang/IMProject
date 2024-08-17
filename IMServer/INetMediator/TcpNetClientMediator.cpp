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

//��ʼ������
bool TcpNetClientMediator::OpenNet() {
	return m_pINet->InitNet();
}
//��������
bool TcpNetClientMediator::SendData(long lSend, char* SendBuf, int nLen) {
	//cout << "TcpNetClientMediator::SendData" << SendBuf << endl;
	return m_pINet->SendData(lSend, SendBuf, nLen);
}
//��������
void TcpNetClientMediator::DealData(long lSend, char* recvBuf, int nLen) {
	cout << "TcpNetClientMediator::DealData" << recvBuf << endl;
}
//�ر�����
void TcpNetClientMediator::CloseNet() {
	m_pINet->UnitNet();
}