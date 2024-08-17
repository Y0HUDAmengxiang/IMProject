#pragma once
#include <string.h>
//使用的端口
#define DEF_UDP_PORT (15875)
#define DEF_TCP_PORT (99723)
//IP地址
#define DEF_IP_ADDR ("192.168.129.1")
//数组长度
#define _DEF_NAME_MAX (100)
#define _UDP_CONTENT_SIZE (1024)
#define _DEF_PROTOCOL_CONT (15)
#define _MAX_FILE_PATH	   (512)
typedef int PackType;
//协议头
#define _DEF_PROTOCOL_BASE          (1000)
//UDP局域网通信软件：上线广播请求，上线回复，聊天请求，下线广播请求
//上线广播请求
#define _DEF_UDP_ONLINE_RQ          (_DEF_PROTOCOL_BASE + 1)
//上线回复
#define _DEF_UDP_ONLINE_RS          (_DEF_PROTOCOL_BASE + 2)
//聊天请求
#define _DEF_UDP_CHAT_RQ            (_DEF_PROTOCOL_BASE + 3)
//下线广播请求
#define _DEF_UDP_OFFLINE_RQ         (_DEF_PROTOCOL_BASE + 4)

//TCP广域网通信软件：注册请求，注册回复，登录请求，登录回复，获取好友信息请求，
//聊天请求，聊天回复，添加好友请求，添加好友回复，下线请求
//注册请求
#define _DEF_TCP_REGISTER_RQ        (_DEF_PROTOCOL_BASE + 5)
//注册回复
#define _DEF_TCP_REGISTER_RS        (_DEF_PROTOCOL_BASE + 6)
//登录请求
#define _DEF_TCP_LOGIN_RQ           (_DEF_PROTOCOL_BASE + 7)
//登录回复
#define _DEF_TCP_LOGIN_RS           (_DEF_PROTOCOL_BASE + 8)
//获取好友信息请求
#define _DEF_TCP_FRIEND_INFO_RQ     (_DEF_PROTOCOL_BASE + 9)
//聊天请求
#define _DEF_TCP_CHAT_RQ            (_DEF_PROTOCOL_BASE + 10)
//聊天回复
#define _DEF_TCP_CHAT_RS            (_DEF_PROTOCOL_BASE + 11)
//添加好友请求
#define _DEF_TCP_ADD_FRIEND_RQ      (_DEF_PROTOCOL_BASE + 12)
//添加好友回复
#define _DEF_TCP_ADD_FRIEND_RS      (_DEF_PROTOCOL_BASE + 13)
//下线请求
#define _DEF_TCP_OFFLINE_RQ         (_DEF_PROTOCOL_BASE + 14)
//邀请群聊请求
#define _DEF_TCP_GROUP_CHAT_RQ		(_DEF_PROTOCOL_BASE + 15)
//邀请群聊回复
#define _DEF_TCP_GROUP_CHAT_RS		(_DEF_PROTOCOL_BASE + 16)
//文件信息
#define _DEF_PROTOCAL_FILE_INFO_RQ  (_DEF_PROTOCOL_BASE + 17)
//文件块
#define _DEF_PROTOCAL_FILE_BLOCK_RQ  (_DEF_PROTOCOL_BASE + 18)
//结果定义
//注册结果
#define register_success     (0)
#define tel_is_used          (1)
#define name_is_exists       (2)

//登录结果
#define login_success        (0)
#define password_error       (1)
//用户不存在：电话号错了
#define user_not_exists      (2)

//聊天结果
#define send_success         (0)
#define send_fail            (1)

//添加好友结果
#define add_success          (0)
#define friend_not_exists    (1)
#define friend_refuse        (2)
#define friend_offline       (3)

//用户状态
#define status_online        (0)
#define status_offline       (1)

//群聊状态
#define user_appect			 (0)
#define user_refuse			 (1)

//协议结构体
// UDP：
//上线广播请求：协议头，主机名，//ip
//上线回复：协议头，主机名，    //ip
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
//聊天请求：协议头，聊天内容，//ip
typedef struct _STRU_UDP_CHAT_RQ
{
	_STRU_UDP_CHAT_RQ() :type(_DEF_UDP_CHAT_RQ)
	{
		memset(content, 0, _UDP_CONTENT_SIZE);
	}
	PackType type;
	char content[_UDP_CONTENT_SIZE];
} _STRU_UDP_CHAT_RQ;
//下线广播请求：协议头，//ip
typedef struct _STRU_UDP_OFFLINE_RQ
{
	_STRU_UDP_OFFLINE_RQ() :type(_DEF_UDP_OFFLINE_RQ)
	{

	}
	PackType type;
	/*long ip;*/
} _STRU_UDP_OFFLINE_RQ;
//TCP：
//注册请求：协议头，昵称，手机号，密码，
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
//注册回复：协议头，注册结果(注册成功，昵称重复，手机号已被注册)
typedef struct _STRU_TCP_REGISTER_RS
{
	_STRU_TCP_REGISTER_RS() :type(_DEF_TCP_REGISTER_RS), result(tel_is_used)
	{

	}
	PackType type;
	PackType result;
} _STRU_TCP_REGISTER_RS;
//登录请求：协议头，手机号，密码
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
//登录回复：协议头，登录结果(登录成功，密码错误，手机号未注册)
typedef struct _STRU_TCP_LOGIN_RS
{
	_STRU_TCP_LOGIN_RS() :type(_DEF_TCP_LOGIN_RS), result(password_error),id(0)
	{

	}
	PackType type;
	PackType result;
	int id;
} _STRU_TCP_LOGIN_RS;
//获取好友信息请求：协议头，好友昵称，头像id，状态，签名，用户id
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
//聊天请求：协议头，聊天内容，好友id，自己的id
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
//聊天回复：协议头，发送结果(发送成功，好友不在线)
typedef struct _STRU_TCP_CHAT_RS
{
	_STRU_TCP_CHAT_RS() :type(_DEF_TCP_CHAT_RS), result(send_fail), friendId(0)
	{

	}
	PackType type;
	int friendId;
	PackType result;
} _STRU_TCP_CHAT_RS;
//添加好友请求：协议头，好友昵称，自己的id，自己的昵称
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
//添加好友回复：协议头，添加结果，好友昵称，自己的ID和好友ID
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
//文件信息：协议头，文件名，文件大小，文件的唯一标识id
struct _STRU_FILE_INFO_RQ {
	int nType;
	char szFileid[_MAX_FILE_PATH];
	char szFILENAME[_MAX_FILE_PATH];
	long long szFileSize;//int： 2G，long long ：8G
};
//下线请求：协议头，自己的id
typedef struct _STRU_TCP_OFFLINE_RQ
{
	_STRU_TCP_OFFLINE_RQ() :type(_DEF_TCP_OFFLINE_RQ), userId(0)
	{

	}
	PackType type;
	PackType userId;
} _STRU_TCP_OFFLINE_RQ;