#ifndef CKERNEL_H
#define CKERNEL_H

#include <QMap>
#include <QObject>
#include "imclientdialog.h"
#include "INetMediator.h"
#include "logindialog.h"
#include <QTextCodec>
#include "chatdialog.h"
#include "config.h"
class CKernel;
typedef void (CKernel::*PFUN)(long lSend,char* recvBuf,int nLen);
class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = 0);
    ~CKernel();
    //初始化协议头数组
    void setFunMap();

    //qt是utf-8的编码方式，vs是GB312
    //QString是utf8，GB2312存在Char*
    void utf8ToGb2312(QString src,char* dest,int nLen);
    QString gb2312ToUtf8(char* src);

    //处理上线请求
    void dealOnlineRq(long lSend,char* recvBuf , int nLen);

    //处理上线回复
    void dealOnlineRs(long lSend,char* recvBuf , int nLen);

    //处理聊天请求
    void dealChatRq(long lSend,char* recvBuf , int nLen);

    //处理下线请求
    void dealOfflineRq(long lSend,char* recvBuf , int nLen);

    //tcp:处理注册回复
    void dealResRs(long lSend,char* recvBuf , int nLen);
    //tcp:处理登陆回复
    void dealLogRs(long lSend,char* recvBuf , int nLen);
    //处理好友信息
    void dealFriendInfo(long lSend,char* recvBuf , int nLen);
    //处理聊天请求
    void dealTcpChatRq(long lSend,char* recvBuf , int nLen);
    //处理聊天回复
    void dealTcpChatRs(long lSend,char* recvBuf , int nLen);
    //处理下线请求
    void dealTcpOfflinRq(long lSend,char* recvBuf , int nLen);
    //添加好友请求
    void dealTcpAddFriendRq(long lSend,char* recvBuf , int nLen);
    //添加好友回复
    void dealTcpAddFriendRs(long lSend,char* recvBuf , int nLen);




private:
    IMClientDialog* m_pImDlg;
    INetMediator* m_pTcpMediator;
    INetMediator* m_pUdpMediator;
    PFUN m_funMap[_DEF_PROTOCOL_CONT];
    LoginDialog* m_pLoginDlg;
    int m_id;
    QString m_name;
    //保存聊天窗口
    QMap<long,ChatDialog*> m_mapIpToChatdlg;
    //保存tcp的useritem
    QMap<int,useritem*>m_mapIdToUserItem;

    //保存tco聊天窗口
    QMap<int,ChatDialog*> m_mapIdToChatdlg;
signals:

public slots:
    //处理接收到的数据
    void slot_ReadyData(long lSend,char* recvBuf ,int nLen);
    void slot_showhatDlg(QString ip);
    //将发送的信息数据发送给CKernel
    void slot_sendContent(QString content, QString ip);
    void slot_sendTcpContent(QString content, int id);
    void slot_closeApp();
    //处理注册信息的数据
    void slot_registerCommit(QString name,QString tel,QString password);
    //处理登录信息的数据
    void slot_LogingCommit(QString tel,QString password);
    //Tcp，显示跟当前用户的聊天窗口
    void slot_showChatTcpDlg(int id);
    //关闭应用程序
    void slot_closeDialog();
    //处理添加好友的信号
    void slot_addFriend();

};

#endif // CKERNEL_H
