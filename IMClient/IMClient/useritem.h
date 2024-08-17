#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>

namespace Ui {
class useritem;
}

class useritem : public QWidget
{
    Q_OBJECT

public:
    explicit useritem(QWidget *parent = 0);
    ~useritem();
    //设置好友信息的函数
    void setFriendInfo(int id,int icon,int statues,QString name,QString feeling,bool bTcp =false);
    //设置用户下线
    void setFriendOffline();
    QString name() const;

private slots:
    void on_pb_icon_clicked();

private:
    Ui::useritem *ui;
    //好友信息
    int m_friendId;
    QString m_name;
    int m_icon;
    //udp挂ip，tcp显示签名
    QString m_feeling;
    int m_statue;
    int m_iconId;
    //标志TCP
    //true是TCP，false是udp
    bool m_bTcp;
signals:
    //udp聊天窗口
    void SIG_showhatDlg(QString ip);
    //tcp聊天窗口
    void SIG_showChatTcpDlg(int id);
};

#endif // USERITEM_H
