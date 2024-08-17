#ifndef IMCLIENTDIALOG_H
#define IMCLIENTDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QVBoxLayout>
#include <QCloseEvent>
#include "useritem.h"
#include <QMap>
namespace Ui {
class IMClientDialog;
}

class IMClientDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_closeApp();
    //添加好友信号
    void SIG_addFriend();

public:
    explicit IMClientDialog(QWidget *parent = 0);
    ~IMClientDialog();
    //添加好友的函数
    void addFriend(long ip, useritem *item);
    //删除好友
    void deleteFriend(long ip);

    //tcp添加好友
    void addTcpFriend(useritem* item);
    //重写关闭事件
    void closeEvent(QCloseEvent* event) override;
    //设置自己的信息
    void setUserInfo(QString name,QString feeling,int iconId);

private slots:
    void on_pb_tools_1_clicked();
   //点击菜单项的槽函数
    void slot_clickedMenu(QAction* action);

private:
    Ui::IMClientDialog *ui;
    //定义一个垂直布局的层
    QVBoxLayout* m_pLayout;
    //定义联系人垂直布局的层
    QVBoxLayout* m_pFriendLayOut;
    //保存好友的ip和对应的useritem
    QMap<long,useritem*> m_mapIpTpUserItem;
    //定义一个菜单栏的对象指针
    QMenu* m_menu;
};

#endif // IMCLIENTDIALOG_H
