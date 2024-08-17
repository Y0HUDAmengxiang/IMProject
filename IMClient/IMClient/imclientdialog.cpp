#include "imclientdialog.h"
#include "ui_imclientdialog.h"
#include <QMessageBox>
#include <QDebug>

IMClientDialog::IMClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IMClientDialog)
{
    ui->setupUi(this);
    //给层new对象
    m_pLayout = new QVBoxLayout;
    //设置margin
    m_pLayout->setContentsMargins(3,0,3,0);
    //设置spacing
    m_pLayout->setSpacing(3);
    //把层
    ui->wdg_list->setLayout(m_pLayout);

    //给层new对象
    m_pFriendLayOut = new QVBoxLayout;
    //设置margin
    m_pFriendLayOut->setContentsMargins(3,0,3,0);
    //设置spaceing
    m_pFriendLayOut->setSpacing(3);
    //把层添加到大空间上
    ui->wdg_list_Tcp->setLayout(m_pFriendLayOut);
    //new一个菜单栏的对象
    m_menu = new QMenu;
    m_menu->addAction("set system");
    m_menu->addAction("add friend");
    connect(m_menu,SIGNAL(triggered(QAction*)),this,SLOT(slot_clickedMenu(QAction*)));

}

IMClientDialog::~IMClientDialog()
{
    delete ui;
}

void IMClientDialog::addFriend(long ip ,useritem *item)
{
    m_mapIpTpUserItem[ip] =item;
    m_pLayout->addWidget(item);
}

void IMClientDialog::deleteFriend(long ip)
{
    auto ite =m_mapIpTpUserItem.find(ip);
    if(ite != m_mapIpTpUserItem.end()){
        useritem* item =*ite;
        if(item){
            item->hide();
            //从父控件移除
            m_pLayout->removeWidget(item);
            delete item;
            item = nullptr;
        }
        m_mapIpTpUserItem.erase(ite);
    }


}

void IMClientDialog::addTcpFriend(useritem *item)
{
    m_pFriendLayOut->addWidget(item);
}

void IMClientDialog::closeEvent(QCloseEvent *event)
{
    //忽略关闭事件，不执行父类的关闭时间
    event->ignore();
    //弹出提示确认用户是否真的需要关闭
    if(QMessageBox::Yes==QMessageBox::question(this,"message","Are you sure?")){
        //通知CKernel，发下线广播关闭应用程序
        Q_EMIT SIG_closeApp();
    }

}

void IMClientDialog::setUserInfo(QString name, QString feeling, int iconId)
{
    ui->lb_name->setText(name);
    ui->le_feeling->setText(feeling);
    ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(iconId)));
}

void IMClientDialog::on_pb_tools_1_clicked()
{
    qDebug()<<__func__;
    //在鼠标点击的位置向上显示一个菜单栏
    QPoint pos = QCursor::pos();
    //获取菜单栏的绝对高度
    QSize size = m_menu->sizeHint();
    m_menu->exec(QPoint(pos.x(),pos.y()-size.height()));

}

void IMClientDialog::slot_clickedMenu(QAction *action)
{
    qDebug()<<__func__;
    //判断点击的菜单项
    if(action->text()=="set system"){
        qDebug()<<"set system";
    }else if(action->text()=="add friend")
    {
        //给kernel发消息
        Q_EMIT SIG_addFriend();
    }
}
