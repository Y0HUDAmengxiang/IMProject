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

//��ʼ������
bool UdpNetMediator::OpenNet() {
	return m_pINet->InitNet();
}
//��������
bool UdpNetMediator::SendData(long lSend, char* SendBuf, int nLen) {
	return m_pINet->SendData(lSend, SendBuf, nLen);
}
//��������
void UdpNetMediator::DealData(long lSend, char* recvBuf, int nLen) {
	cout << "UdpNetMediator::DealData: " << recvBuf << endl;
}
//�ر�����
void UdpNetMediator::CloseNet() {
	m_pINet->UnitNet();
}