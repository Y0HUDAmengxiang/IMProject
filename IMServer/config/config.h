#pragma once
#include <string.h>
//ʹ�õĶ˿�
#define DEF_UDP_PORT (15875)
#define DEF_TCP_PORT (99723)
//IP��ַ
#define DEF_IP_ADDR ("192.168.129.1")
//���鳤��
#define _DEF_NAME_MAX (100)
#define _UDP_CONTENT_SIZE (1024)
#define _DEF_PROTOCOL_CONT (15)
#define _MAX_FILE_PATH	   (512)
typedef int PackType;
//Э��ͷ
#define _DEF_PROTOCOL_BASE          (1000)
//UDP������ͨ����������߹㲥�������߻ظ��������������߹㲥����
//���߹㲥����
#define _DEF_UDP_ONLINE_RQ          (_DEF_PROTOCOL_BASE + 1)
//���߻ظ�
#define _DEF_UDP_ONLINE_RS          (_DEF_PROTOCOL_BASE + 2)
//��������
#define _DEF_UDP_CHAT_RQ            (_DEF_PROTOCOL_BASE + 3)
//���߹㲥����
#define _DEF_UDP_OFFLINE_RQ         (_DEF_PROTOCOL_BASE + 4)

//TCP������ͨ�������ע������ע��ظ�����¼���󣬵�¼�ظ�����ȡ������Ϣ����
//������������ظ�����Ӻ���������Ӻ��ѻظ�����������
//ע������
#define _DEF_TCP_REGISTER_RQ        (_DEF_PROTOCOL_BASE + 5)
//ע��ظ�
#define _DEF_TCP_REGISTER_RS        (_DEF_PROTOCOL_BASE + 6)
//��¼����
#define _DEF_TCP_LOGIN_RQ           (_DEF_PROTOCOL_BASE + 7)
//��¼�ظ�
#define _DEF_TCP_LOGIN_RS           (_DEF_PROTOCOL_BASE + 8)
//��ȡ������Ϣ����
#define _DEF_TCP_FRIEND_INFO_RQ     (_DEF_PROTOCOL_BASE + 9)
//��������
#define _DEF_TCP_CHAT_RQ            (_DEF_PROTOCOL_BASE + 10)
//����ظ�
#define _DEF_TCP_CHAT_RS            (_DEF_PROTOCOL_BASE + 11)
//��Ӻ�������
#define _DEF_TCP_ADD_FRIEND_RQ      (_DEF_PROTOCOL_BASE + 12)
//��Ӻ��ѻظ�
#define _DEF_TCP_ADD_FRIEND_RS      (_DEF_PROTOCOL_BASE + 13)
//��������
#define _DEF_TCP_OFFLINE_RQ         (_DEF_PROTOCOL_BASE + 14)
//����Ⱥ������
#define _DEF_TCP_GROUP_CHAT_RQ		(_DEF_PROTOCOL_BASE + 15)
//����Ⱥ�Ļظ�
#define _DEF_TCP_GROUP_CHAT_RS		(_DEF_PROTOCOL_BASE + 16)
//�ļ���Ϣ
#define _DEF_PROTOCAL_FILE_INFO_RQ  (_DEF_PROTOCOL_BASE + 17)
//�ļ���
#define _DEF_PROTOCAL_FILE_BLOCK_RQ  (_DEF_PROTOCOL_BASE + 18)
//�������
//ע����
#define register_success     (0)
#define tel_is_used          (1)
#define name_is_exists       (2)

//��¼���
#define login_success        (0)
#define password_error       (1)
//�û������ڣ��绰�Ŵ���
#define user_not_exists      (2)

//������
#define send_success         (0)
#define send_fail            (1)

//��Ӻ��ѽ��
#define add_success          (0)
#define friend_not_exists    (1)
#define friend_refuse        (2)
#define friend_offline       (3)

//�û�״̬
#define status_online        (0)
#define status_offline       (1)

//Ⱥ��״̬
#define user_appect			 (0)
#define user_refuse			 (1)

//Э��ṹ��
// UDP��
//���߹㲥����Э��ͷ����������//ip
//���߻ظ���Э��ͷ����������    //ip
typedef struct _STRU_UDP_ONLINE
{
	_STRU_UDP_ONLINE() :type(_DEF_UDP_ONLINE_RQ) /*ip(0)*/
	{
		memset(name, 0, _DEF_NAME_MAX);
	}
	PackType type;
	/*long ip;*/
	char name[_DEF_NAME_MAX];
}_STRU_UDP_ONLINE;
//��������Э��ͷ���������ݣ�//ip
typedef struct _STRU_UDP_CHAT_RQ
{
	_STRU_UDP_CHAT_RQ() :type(_DEF_UDP_CHAT_RQ)
	{
		memset(content, 0, _UDP_CONTENT_SIZE);
	}
	PackType type;
	char content[_UDP_CONTENT_SIZE];
} _STRU_UDP_CHAT_RQ;
//���߹㲥����Э��ͷ��//ip
typedef struct _STRU_UDP_OFFLINE_RQ
{
	_STRU_UDP_OFFLINE_RQ() :type(_DEF_UDP_OFFLINE_RQ)
	{

	}
	PackType type;
	/*long ip;*/
} _STRU_UDP_OFFLINE_RQ;
//TCP��
//ע������Э��ͷ���ǳƣ��ֻ��ţ����룬
typedef struct _STRU_TCP_REGISTER_RQ
{
	_STRU_TCP_REGISTER_RQ() :type(_DEF_TCP_REGISTER_RQ)
	{
		memset(name, 0, _DEF_NAME_MAX);
		memset(tel, 0, _DEF_NAME_MAX);
		memset(password, 0, _DEF_NAME_MAX);
	}
	PackType type;
	char name[_DEF_NAME_MAX];
	char tel[_DEF_NAME_MAX];
	char password[_DEF_NAME_MAX];
} _STRU_TCP_REGISTER_RQ;
//ע��ظ���Э��ͷ��ע����(ע��ɹ����ǳ��ظ����ֻ����ѱ�ע��)
typedef struct _STRU_TCP_REGISTER_RS
{
	_STRU_TCP_REGISTER_RS() :type(_DEF_TCP_REGISTER_RS), result(tel_is_used)
	{

	}
	PackType type;
	PackType result;
} _STRU_TCP_REGISTER_RS;
//��¼����Э��ͷ���ֻ��ţ�����
typedef struct _STRU_TCP_LOGIN_RQ
{
	_STRU_TCP_LOGIN_RQ() :type(_DEF_TCP_LOGIN_RQ)
	{
		memset(tel, 0, _DEF_NAME_MAX);
		memset(password, 0, _DEF_NAME_MAX);
	}
	PackType type;
	char tel[_DEF_NAME_MAX];
	char password[_DEF_NAME_MAX];
} _STRU_TCP_LOGIN_RQ;
//��¼�ظ���Э��ͷ����¼���(��¼�ɹ�����������ֻ���δע��)
typedef struct _STRU_TCP_LOGIN_RS
{
	_STRU_TCP_LOGIN_RS() :type(_DEF_TCP_LOGIN_RS), result(password_error),id(0)
	{

	}
	PackType type;
	PackType result;
	int id;
} _STRU_TCP_LOGIN_RS;
//��ȡ������Ϣ����Э��ͷ�������ǳƣ�ͷ��id��״̬��ǩ�����û�id
typedef struct _STRU_TCP_FRIEND_INFO_RQ
{
	_STRU_TCP_FRIEND_INFO_RQ() :type(_DEF_TCP_FRIEND_INFO_RQ), iconId(0), status(status_online), id(0)
	{
		memset(friendName, 0, _DEF_NAME_MAX);
		memset(feeling, 0, _DEF_NAME_MAX);
	}
	PackType type;
	char friendName[_DEF_NAME_MAX];
	int id;
	int iconId;
	int status;
	char feeling[_DEF_NAME_MAX];
} _STRU_TCP_FRIEND_INFO_RQ;
//��������Э��ͷ���������ݣ�����id���Լ���id
typedef struct _STRU_TCP_CHAT_RQ
{
	_STRU_TCP_CHAT_RQ() :type(_DEF_TCP_CHAT_RQ), userId(0), friendId(0)
	{
		memset(content, 0, _UDP_CONTENT_SIZE);
	}
	PackType type;
	char content[_UDP_CONTENT_SIZE];
	PackType userId;
	PackType friendId;
} _STRU_TCP_CHAT_RQ;
//����ظ���Э��ͷ�����ͽ��(���ͳɹ������Ѳ�����)
typedef struct _STRU_TCP_CHAT_RS
{
	_STRU_TCP_CHAT_RS() :type(_DEF_TCP_CHAT_RS), result(send_fail), friendId(0)
	{

	}
	PackType type;
	int friendId;
	PackType result;
} _STRU_TCP_CHAT_RS;
//��Ӻ�������Э��ͷ�������ǳƣ��Լ���id���Լ����ǳ�
typedef struct _STRU_TCP_ADD_FRIEND_RQ
{
	_STRU_TCP_ADD_FRIEND_RQ() :type(_DEF_TCP_ADD_FRIEND_RQ), userId(0)
	{
		memset(friendName, 0, _DEF_NAME_MAX);
		memset(name, 0, _DEF_NAME_MAX);
	}
	PackType type;
	char friendName[_DEF_NAME_MAX];
	PackType userId;
	char name[_DEF_NAME_MAX];
} _STRU_TCP_ADD_FRIENDP_RQ;
//��Ӻ��ѻظ���Э��ͷ����ӽ���������ǳƣ��Լ���ID�ͺ���ID
typedef struct _STRU_TCP_ADD_FRIEND_RS
{
	_STRU_TCP_ADD_FRIEND_RS() :type(_DEF_TCP_ADD_FRIEND_RS), userId(0), friendId(0), result(friend_not_exists)
	{
		memset(friendName, 0, _DEF_NAME_MAX);
	}
	PackType type;
	int userId;
	int friendId;
	PackType result;
	char friendName[_DEF_NAME_MAX];
} _STRU_TCP_ADD_FRIENDP_RS;
//�ļ���Ϣ��Э��ͷ���ļ������ļ���С���ļ���Ψһ��ʶid
struct _STRU_FILE_INFO_RQ {
	int nType;
	char szFileid[_MAX_FILE_PATH];
	char szFILENAME[_MAX_FILE_PATH];
	long long szFileSize;//int�� 2G��long long ��8G
};
//��������Э��ͷ���Լ���id
typedef struct _STRU_TCP_OFFLINE_RQ
{
	_STRU_TCP_OFFLINE_RQ() :type(_DEF_TCP_OFFLINE_RQ), userId(0)
	{

	}
	PackType type;
	PackType userId;
} _STRU_TCP_OFFLINE_RQ;