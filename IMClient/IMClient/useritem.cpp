#include "useritem.h"
#include "ui_useritem.h"
#include "config.h"
#include <QBitmap>
useritem::useritem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::useritem),m_bTcp(false)
{
    ui->setupUi(this);
}

useritem::~useritem()
{
    delete ui;
}

void useritem::setFriendInfo(int id, int icon, int statues, QString name, QString feeling,bool bTcp)
{
    m_bTcp =bTcp;
    //保存好友的信息
    m_friendId = id;
    m_iconId = icon;
    m_statue = statues;
    m_name = name;
    m_feeling = feeling;
    //把信息设置到界面上显示
    ui->lb_name->setText(m_name);
    ui->lb_feeling->setText(m_feeling);
    //加载头像图片
    QString path = QString(":/tx/%1.png").arg(m_iconId);
    if(status_online == m_statue)
    {
        //在线亮显
        ui->pb_icon->setIcon(QIcon(path));

    }else
    {
        //不在线，头像暗显
        QBitmap bmp;
        bmp.load(path);
        ui->pb_icon->setIcon(bmp);
    }
    this->repaint();

}

void useritem::setFriendOffline()
{
    //改变状态
    m_statue =status_offline;
    //头像暗示
    QString path = QString(":/tx/%1.png").arg(m_iconId);
    QBitmap bmp;
    bmp.load(path);
    ui->pb_icon->setIcon(bmp);
    this->repaint();

}

void useritem::on_pb_icon_clicked()
{
    //给Kernel发信号 显示跟当前用户的聊天窗口

    if(m_bTcp){
        //tcp：发好友的id
        Q_EMIT SIG_showChatTcpDlg(m_friendId);
    }
    else
    {
        //udp：发好友的ip
        QString ip;
        ip=m_feeling;
        Q_EMIT SIG_showhatDlg(ip);
    }


}

QString useritem::name() const
{
    return m_name;
}
