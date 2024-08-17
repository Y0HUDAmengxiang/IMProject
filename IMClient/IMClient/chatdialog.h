#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QWidget
{
    Q_OBJECT
signals:
    void SIG_sendContent(QString content, QString ip);
    void SIG_sendTcpContent(QString content,int id);

public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
    void setDialogInfo(QString ip,int id = -1);
    //设置聊天内容到窗口上
    void setChatContent(QString content);

private slots:
    void on_pb_send_clicked();

private:
    Ui::ChatDialog *ui;
    //udpb保存ip,Tcp保存的昵称
    QString m_ip;
    //用与保存tcp的id
    int m_id;
};

#endif // CHATDIALOG_H
