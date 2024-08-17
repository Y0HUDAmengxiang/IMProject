#pragma once
#include "INetMediator.h"
#include "CMySql.h"
#include "config.h"
#include <map>

using namespace std;
//�����еĳ�Ա����ָ��
class CKernel;
typedef void (CKernel ::* PFUN)(long lSend, char* recvBuf, int nLen);
class CKernel {
public:
	static CKernel* pKernel;
	CKernel();
	~CKernel();
public:
	//��ʼ������ָ��:
	void setFunMap();
	//�򿪷�����
	bool startServer();
	//�رշ�����
	void CloseServer();
	//���������յ�������
	void ReadyData(long lSend, char* recvBuf, int nLen);
	//����ע������
	void dealRegisterRq(long lSend, char* recvBuf, int nLen);
	//�����¼����
	void dealLoginRq(long lSend, char* recvBuf, int nLen);
	//��ȡ���ѵ���Ϣ�б������Լ���
	void getFriendInfoList(int userId);
	//����id����Ϣ
	void getUserInfoById(int id,_STRU_TCP_FRIEND_INFO_RQ* info);
	//������������
	void dealChatRq(long lSend, char* recvBuf, int nLen);
	//������������
	void dealOfflineRq(long lSend, char* recvBuf, int nLen);
	//����Ӻ�������
	void dealAddFriendRq(long lSend, char* recvBuf, int nLen);
	//������Ӻ��ѻظ�
	void dealAddFriendRs(long lSend, char* recvBuf, int nLen);
	PFUN m_funMap[_DEF_PROTOCOL_CONT];
	//����id��SOCKET��map���ڱ���
	map<int, SOCKET>m_mapidToSocket;
private:
	INetMediator* m_pMediator;
	CMySql m_Sql;
	

};

