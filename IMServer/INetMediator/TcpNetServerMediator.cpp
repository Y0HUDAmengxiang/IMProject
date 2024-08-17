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

//��ʼ������
bool TcpNetServerMediator::OpenNet() {
	return m_pINet->InitNet();
}
//��������
bool TcpNetServerMediator::SendData(long lSend, char* SendBuf, int nLen) {
	return m_pINet->SendData(lSend, SendBuf, nLen);
}
//��������
void TcpNetServerMediator::DealData(long lSend, char* recvBuf, int nLen) {

	CKernel::pKernel->ReadyData(lSend, recvBuf, nLen);
	
	
}
//�ر�����
void TcpNetServerMediator::CloseNet() {
	m_pINet->UnitNet();
}