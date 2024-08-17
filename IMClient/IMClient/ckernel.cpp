#include "ckernel.h"
#include "UdpNetMediator.h"
#include "TcpNetClientMediator.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include "config.h"
#include "INet.h"
/*
 *
 * 信号和槽机制是QT里特有的机制用来发送数据
 * 信号是发数据的
 * 槽函数是接受数据的类
 * 使用信号和槽的步骤
 * 1.使用信号和槽机制的类必须继承自QObject
 * 2.需要有Q_OBJECT
 * 3.发送数据的类里面定义信号signals
 * 4.在接受数据的类里面声明并实显槽函数 slots
 * 5.在接收数据的类里边，发送信号对象new出来以后绑定信号和槽函数
 * connect(发送数据的对象，发送数据的信号，接收信号的对象，槽函数)
*/
CKernel::CKernel(QObject *parent) : QObject(parent),m_id(0)
{
    setFunMap();
    //new 一个 clientdialog对象
    m_pImDlg = new IMClientDialog;
    //m_pImDlg->show();
    connect(m_pImDlg,SIGNAL(SIG_closeApp()),this,SLOT(slot_closeApp()));
    //绑定添加好友的信号和槽函数
    connect(m_pImDlg,SIGNAL(SIG_addFriend()),this,SLOT(slot_addFriend()));

    m_pUdpMediator = new UdpNetMediator;

    m_pTcpMediator =new TcpNetClientMediator;
    //new一个登录和注册界面的对象
    m_pLoginDlg =new LoginDialog;
    m_pLoginDlg->show();
    connect(m_pLoginDlg,SIGNAL(SIG_resgisterCommit(QString,QString,QString))
            ,this,SLOT(slot_registerCommit(QString,QString,QString)));
    connect(m_pLoginDlg,SIGNAL(SIG_logingCommit(QString,QString)),
            this,SLOT(slot_LogingCommit(QString,QString)));
    connect(m_pLoginDlg,SIGNAL(SIG_closeDialog()),this,
            SLOT(slot_closeDialog()));
    if(!m_pUdpMediator->OpenNet()){
        QMessageBox::about(m_pImDlg,"message","open Udp net fail");
        exit(1);
    }

    if(!m_pTcpMediator->OpenNet()){
        QMessageBox::about(m_pImDlg,"message","open Udp net fail");
        exit(1);
    }
    //绑定接收所有处理接收数据的函数
    connect(m_pUdpMediator,SIGNAL(SIG_ReadyData(long,char*,int)),
            this,SLOT(slot_ReadyData(long,char*,int)));
    connect(m_pTcpMediator,SIGNAL(SIG_ReadyData(long,char*,int)),this,
            SLOT(slot_ReadyData(long,char*,int)));
    //客户端给服务器发个hello
//    _STRU_UDP_ONLINE rq;
//    strcpy(rq.name,"mamama");
//    m_pTcpMediator->SendData(789,(char*)&rq,sizeof(rq));
    //udp测试代码
//    _STRU_UDP_ONLINE rq;
//    gethostname(rq.name,sizeof(rq));
//    m_pUdpMediator->SendData(INADDR_BROADCAST,(char*)&rq,sizeof(rq));

}

CKernel::~CKernel(){
   slot_closeDialog();
}

void CKernel::setFunMap()
{
    qDebug()<<__func__;
    memset(m_funMap,0,sizeof(m_funMap));
    m_funMap[_DEF_UDP_ONLINE_RQ - _DEF_PROTOCOL_BASE - 1 ]=&CKernel::dealOnlineRq;
    m_funMap[_DEF_UDP_ONLINE_RS - _DEF_PROTOCOL_BASE - 1 ]=&CKernel::dealOnlineRs;
    m_funMap[_DEF_UDP_CHAT_RQ - _DEF_PROTOCOL_BASE -1 ]=&CKernel::dealChatRq;
    m_funMap[_DEF_UDP_OFFLINE_RQ - _DEF_PROTOCOL_BASE - 1 ]= &CKernel::dealOfflineRq;
    m_funMap[_DEF_TCP_REGISTER_RS - _DEF_PROTOCOL_BASE -1] = &CKernel::dealResRs;
    m_funMap[_DEF_TCP_LOGIN_RS - _DEF_PROTOCOL_BASE -1] = &CKernel::dealLogRs;
    m_funMap[_DEF_TCP_FRIEND_INFO_RQ - _DEF_PROTOCOL_BASE -1] = &CKernel::dealFriendInfo;
    m_funMap[_DEF_TCP_CHAT_RQ - _DEF_PROTOCOL_BASE -1] =&CKernel::dealTcpChatRq;
    m_funMap[_DEF_TCP_CHAT_RS - _DEF_PROTOCOL_BASE -1] =&CKernel::dealTcpChatRs;
    m_funMap[_DEF_TCP_OFFLINE_RQ - _DEF_PROTOCOL_BASE -1] =&CKernel::dealTcpOfflinRq;
    m_funMap[_DEF_TCP_ADD_FRIEND_RQ - _DEF_PROTOCOL_BASE -1] =&CKernel::dealTcpAddFriendRq;
    m_funMap[_DEF_TCP_ADD_FRIEND_RS - _DEF_PROTOCOL_BASE -1] =&CKernel::dealTcpAddFriendRs;
}

void CKernel::utf8ToGb2312(QString src, char *dest, int nLen)
{
    QTextCodec* pCode = QTextCodec::codecForName("gb2312");
    QByteArray ba = pCode->fromUnicode(src);
    if(ba.length() <= nLen ){
        memcpy(dest,ba.data(),ba.length());
    }
}

QString CKernel::gb2312ToUtf8(char *src)
{
    QTextCodec* pCodec =QTextCodec::codecForName("gb2312");
    return pCodec->toUnicode(src);
}

void CKernel::dealOnlineRq(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_UDP_ONLINE* rq = (_STRU_UDP_ONLINE*)recvBuf;

     useritem* item = new useritem;
    //2.把好友添加到列表上
    struct in_addr addr;
    addr.S_un.S_addr =lSend;

    item->setFriendInfo(0,7,status_online,rq->name,inet_ntoa(addr));
    //把好友加到列表上
    m_pImDlg->addFriend(lSend,item);
    //绑定显示聊天窗口的信号和槽函数
    connect(item,SIGNAL(SIG_showhatDlg(QString)),
            this,SLOT(slot_showhatDlg(QString)));
    //3.new一个和这个人的聊天窗口
    ChatDialog* chat = new ChatDialog;

    chat->setDialogInfo(inet_ntoa(addr));
    //保存到map中
    m_mapIpToChatdlg[lSend] = chat;
    //绑定发送聊天内容的槽函数
    connect(chat,SIGNAL(SIG_sendContent(QString,QString)),this,SLOT(slot_sendContent(QString,QString)));
    //3.判断是不是自己的上线请求，如果是自己的就不会回复
    set<long> ipList =INet::GetipList();
    //获取本地ip地址列表

    //判断发送数据的ip是否在本地ip地址的列表上
    if(ipList.count(lSend) > 0){
        return ;
    }
    //4.给好友写一个回复包
    _STRU_UDP_ONLINE rs;
    rs.type = _DEF_UDP_ONLINE_RS;
    gethostname(rs.name,sizeof(rs.name));
    m_pUdpMediator->SendData(lSend,(char*)&rs,sizeof(rs));

}

void CKernel::dealOnlineRs(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;



}

void CKernel::dealChatRq(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_UDP_CHAT_RQ* rq=(_STRU_UDP_CHAT_RQ*)recvBuf;
    if(m_mapIpToChatdlg.find(lSend) != m_mapIpToChatdlg.end()){
        //有窗口显示
        ChatDialog* chat = m_mapIpToChatdlg[lSend];

        //设置聊天内容到窗口上
        chat->setChatContent(rq->content);
        chat->showNormal();

    }
}

void CKernel::dealOfflineRq(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;

    //1.回收这个人的聊天窗口
    auto ite = m_mapIpToChatdlg.find(lSend);
    if(ite!=m_mapIpToChatdlg.end())
    if(m_mapIpToChatdlg.count(lSend)>0){
        ChatDialog* chat = *ite;
        if(chat){
            chat->hide();
            delete chat;
            chat=nullptr;
        }
        m_mapIpToChatdlg.erase(ite);
    }
    //2.把好友从列表上移除
}
//tcp:处理注册回复
void CKernel::dealResRs(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_REGISTER_RS* rs =(_STRU_TCP_REGISTER_RS*)recvBuf;

    //2.根据注册结果显示提示信息
    switch(rs->result){
    case register_success:
        QMessageBox::about(m_pLoginDlg,"message","register success");
        break;
    case tel_is_used:
        QMessageBox::about(m_pLoginDlg,"message","tel is user");
        break;
    case name_is_exists:
        QMessageBox::about(m_pLoginDlg,"message","name is used");
        break;
    default:
        break;
    }
}

void CKernel::dealLogRs(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_LOGIN_RS* rs = (_STRU_TCP_LOGIN_RS*)recvBuf;
    //2.根据登陆结果显示提示信息
    switch(rs->result){
    case login_success:
        {
            m_pLoginDlg->hide();
            m_pImDlg->showNormal();
            //保存自己的id
            m_id =rs->id;
        }
        break;
    case password_error:
        QMessageBox::about(m_pLoginDlg,"message","password_error");
        break;
    case user_not_exists:
        QMessageBox::about(m_pLoginDlg,"message","tel is not bao cun");
        break;
    default:
        break;
    }

}
//处理好友信息
void CKernel::dealFriendInfo(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_FRIEND_INFO_RQ* rq =(_STRU_TCP_FRIEND_INFO_RQ*)recvBuf;
    QString name = gb2312ToUtf8(rq->friendName);
    QString feeling = gb2312ToUtf8(rq->feeling);
    //2.判断是不是自己
    if(rq->id == m_id){
        //保存自己的昵称
        m_name = name;
        //如果是自己的信息，就设置
        m_pImDlg->setUserInfo(name,feeling,rq->iconId);
        return;
    }

    //3.是好友，需要判断这个好友是否已在类表上

    if(m_mapIdToUserItem.count(rq->id)>0){
        //就更新好友信息
        useritem* item = m_mapIdToUserItem[rq->id];
        item->setFriendInfo(rq->id,rq->iconId,rq->status,name,feeling,true);
    }
    else
    {
        //不在列表上，就new一个新的useritem
        useritem* item =new useritem;
        //设置useritem
        item->setFriendInfo(rq->id,rq->iconId,rq->status,name,feeling,true);
        //把useritem添加到列表上
        m_pImDlg->addTcpFriend(item);
        //new一个和这个好友的聊天窗口
         m_mapIdToUserItem[rq->id] = item;
          //绑定显示聊天窗口的槽函数
          connect(item,SIGNAL(SIG_showChatTcpDlg(int)),
                  this,SLOT(slot_showChatTcpDlg(int)));
        //设置聊天窗口
          ChatDialog* chat =new ChatDialog;
          chat->setDialogInfo(name,rq->id);
          //把聊天窗口保存到map中
          m_mapIdToChatdlg[rq->id]= chat;
          connect(chat,SIGNAL(SIG_sendTcpContent(QString,int))
                  ,this,SLOT(slot_sendTcpContent(QString,int)));
    }
}

void CKernel::dealTcpChatRq(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_CHAT_RQ* rq = (_STRU_TCP_CHAT_RQ*)recvBuf;
    //2.根据id找到聊天窗口
    if(m_mapIdToChatdlg.count(rq->userId)>0){
        //取出聊天窗口
        ChatDialog* chat =m_mapIdToChatdlg[rq->userId];
        /*
         * 为社么用userId因为在这个包只是转发过来的接收到的数据没变，userId实际上不是B自己的而是A的
         */
        //设置聊天内容到窗口上
        chat->setChatContent(rq->content);

        //显示聊天窗口
        chat->showNormal();
    }

}

void CKernel::dealTcpChatRs(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;

    //1.拆包
     _STRU_TCP_CHAT_RS* rs = (_STRU_TCP_CHAT_RS*)recvBuf;
     qDebug()<<"rs:"<<rs->friendId;
    //2.根据id找聊天窗口
    if(m_mapIdToChatdlg.count(rs->friendId)>0){
        //取出聊天窗口
        ChatDialog* chat =m_mapIdToChatdlg[rs->friendId];
        //设置好友不在线到聊天窗口上
        chat->setChatContent(QString("好友不在线"));
        //显示聊天窗口
        chat->showNormal();
    }
}

void CKernel::dealTcpOfflinRq(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_OFFLINE_RQ* rq = (_STRU_TCP_OFFLINE_RQ*) recvBuf;
    //2.找到id将头像暗显示
    if(m_mapIdToUserItem.count(rq->userId)>0){
        useritem* item = m_mapIdToUserItem[rq->userId];
        //设置头像下线状态
        item->setFriendOffline();
    }
}

void CKernel::dealTcpAddFriendRq(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_ADD_FRIENDP_RQ* rq =(_STRU_TCP_ADD_FRIENDP_RQ*)recvBuf;

    //2.弹出提示框，询问用户同意还是拒绝
    _STRU_TCP_ADD_FRIENDP_RS rs;
    if(QMessageBox::Yes == QMessageBox::question(m_pImDlg,"message",QString("[%1] want to add friend with you").arg(rq->friendName))){
        //如果同意、
        rs.result =add_success;

    }else
    {
        //如果不同意
        rs.result = friend_refuse;
    }
    //不管同不同意，都会发送给服务端
     rs.userId = rq->userId;
     rs.friendId =m_id;
     strcpy(rs.friendName,rq->friendName);

     m_pTcpMediator->SendData(43,(char*)&rs,sizeof(rs));

}

void CKernel::dealTcpAddFriendRs(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    //1.拆包
    _STRU_TCP_ADD_FRIENDP_RS* rs =(_STRU_TCP_ADD_FRIENDP_RS*)recvBuf;
    //添加好友结果
//    #define add_success          (0)
//    #define friend_not_exists    (1)
//    #define friend_refuse        (2)
//    #define friend_offline       (3)
    //2.根据添加结果显示出提示信息
    QString friendName = gb2312ToUtf8(rs->friendName);
    switch(rs->result){
    case add_success:
        QMessageBox::about(m_pImDlg,"message",QString("add [%1] sucess").arg(rs->friendName));
        break;
    case friend_offline:
        QMessageBox::about(m_pImDlg,"message",QString("[%1]offline ").arg(rs->friendName));
        break;
    case friend_not_exists:
        QMessageBox::about(m_pImDlg,"message",QString(" [%1] is not exits").arg(rs->friendName));
        break;
    case friend_refuse:
        QMessageBox::about(m_pImDlg,"message",QString(" [%1] is refuse").arg(rs->friendName));
        break;
    }
}

void CKernel::slot_ReadyData(long lSend, char *recvBuf, int nLen)
{
    qDebug()<<__func__;
    PackType type =*(PackType*)recvBuf;
    //根据协议头走到对应的处理函数
    //计算数组下标
    int index = type - _DEF_PROTOCOL_BASE -1;
    if(index >= 0 && index < _DEF_PROTOCOL_CONT){
        PFUN pf = m_funMap[index];
        if(pf){
            (this->*pf)(lSend ,recvBuf ,nLen);
        }
        else
        {
            qDebug()<<"type : "<<type;
        }
    }
    else
    {
        qDebug()<<"type : "<<type;
    }
    delete[] recvBuf;
}

void CKernel::slot_showhatDlg(QString ip)
{
    //判断有没有这个窗口
    long lIp = inet_addr(ip.toStdString().c_str());
    if(m_mapIpToChatdlg.find(lIp) != m_mapIpToChatdlg.end()){
        //有窗口显示
        ChatDialog* chat = m_mapIpToChatdlg[lIp];
        chat->showNormal();
    }
}

void CKernel::slot_sendContent(QString content, QString ip)
{
    //打包
    _STRU_UDP_CHAT_RQ rq;
    memcpy(rq.content , content.toStdString().c_str(), content.length());
    //发送给对端
    long lIp =inet_addr(ip.toStdString().c_str());
    m_pUdpMediator->SendData(lIp,(char*)&rq,sizeof(rq));
}

void CKernel::slot_sendTcpContent(QString content, int id)
{
    //打包
    _STRU_TCP_CHAT_RQ rq;
    memcpy(rq.content , content.toStdString().c_str(), content.length());
    //发送给对端
    rq.friendId = id;
    rq.userId = m_id;
    m_pTcpMediator->SendData(890,(char*)&rq,sizeof(rq));
}
//处理下线信号
void CKernel::slot_closeApp()
{
    //1.发下线通知
    _STRU_UDP_OFFLINE_RQ rq;
    m_pUdpMediator->SendData(INADDR_BROADCAST,(char*)&rq,sizeof(rq));
   //2.tcp的下线通知
    _STRU_TCP_OFFLINE_RQ trq;
    trq.userId =m_id;
    m_pTcpMediator->SendData(890,(char*)&trq,sizeof(trq));

    //回收资源，退出进程
    slot_closeDialog();

}
//处理注册信息

void CKernel::slot_registerCommit(QString name, QString tel, QString password)
{
    //1.封包发送给服务端
    _STRU_TCP_REGISTER_RQ rq;
    //memcpy(rq.name,name.toStdString().c_str(),name.length());
    utf8ToGb2312(name,rq.name,sizeof(rq.name));
    memcpy(rq.tel,tel.toStdString().c_str(),tel.length());
    memcpy(rq.password,password.toStdString().c_str(),password.length());

    //2.发送给服务端
    m_pTcpMediator->SendData(890,(char*)&rq,sizeof(rq));

}

//处理用户登陆信息
void CKernel::slot_LogingCommit(QString tel, QString password)
{
    qDebug()<<__func__;
    //1.打包
    _STRU_TCP_LOGIN_RQ rq;
    strcpy(rq.password,password.toStdString().c_str());
    strcpy(rq.tel,tel.toStdString().c_str());
    m_pTcpMediator->SendData(890,(char*)&rq,sizeof(rq));
}

void CKernel::slot_showChatTcpDlg(int id)
{
    //判断有没有窗口
    if(m_mapIdToChatdlg.count(id)> 0){
        ChatDialog* chat = m_mapIdToChatdlg[id];
        chat->showNormal();
    }
}

void CKernel::slot_closeDialog()
{
    qDebug()<<__func__;
    //回收资源
        if(m_pImDlg){
            m_pImDlg->hide();
            delete m_pImDlg;
            m_pImDlg = nullptr;
        }

        if(m_pUdpMediator){
            delete m_pUdpMediator;
            m_pUdpMediator = nullptr;
        }

        if(m_pLoginDlg){
            m_pLoginDlg->hide();
            delete m_pLoginDlg;
            m_pLoginDlg =nullptr;
        }

        if(m_pTcpMediator){
            delete m_pTcpMediator;
            m_pTcpMediator = nullptr;
        }

        for(auto ite = m_mapIpToChatdlg.begin();ite!=m_mapIpToChatdlg.begin();){
            ChatDialog* chat =*ite;
            if(chat){
                chat->hide();
                delete chat;
                chat = nullptr;
            }
            ite = m_mapIpToChatdlg.erase(ite);
        }
        for(auto ite = m_mapIdToChatdlg.begin();ite!=m_mapIdToChatdlg.begin();){
            ChatDialog* chat =*ite;
            if(chat){
                chat->hide();
                delete chat;
                chat = nullptr;
            }
            ite = m_mapIdToChatdlg.erase(ite);
        }

        //3.推迟进程
        //退出程序
}

void CKernel::slot_addFriend()
{
    qDebug()<<__func__;
    //1.弹出询问窗口，让用户输入昵称
    QString name = QInputDialog::getText(m_pImDlg,"add friend","please input friend name:");
    QString nameTemp =name;
    qDebug()<<name;
    //2.校验昵称是否是空或者去按空格
    if(name.isEmpty()||nameTemp.remove(" ").isEmpty()){
        QMessageBox::about(m_pImDlg,"message","name is null");
        return;
    }
    //3.校验昵称是否是自己
    if(name == m_name){
        QMessageBox::about(m_pImDlg,"message","name is your name");
          return;
    }
    //4.校验昵称是否已经是好友
    for(auto ite =m_mapIdToUserItem.begin();ite!=m_mapIdToUserItem .end();ite++){
        useritem* item =*ite;
        if(item->name() == name){
            QMessageBox::about(m_pImDlg,"message",QString("[%1] is already your friend").arg(name));
              return;
        }
    }
    //5.给服务端添加好友请求
    _STRU_TCP_ADD_FRIENDP_RQ rq;
    rq.userId =m_id;
    strcpy(rq.name,m_name.toStdString().c_str());
    //memcpy(rq.friendName,name.toStdString().c_str(),name.length());
    utf8ToGb2312(name,rq.friendName,sizeof(rq.friendName));
    m_pTcpMediator->SendData(890,(char*)&rq,sizeof(rq));

}
//字符串类型：char* std::string QString
//std::string QString是封装的类，char*是基础类型（可以给其他类赋值）
