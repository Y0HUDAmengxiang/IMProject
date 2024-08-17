#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
signals:
    //把注册信息发送个KErnel
    void SIG_resgisterCommit(QString name,QString tel,QString password);
    //处理登录信息
    void SIG_logingCommit(QString tel,QString password);

    void SIG_closeDialog();

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    //重写关闭事件
    void closeEvent(QCloseEvent* event);
private slots:
    void on_pb_log_Ok_clicked();

    void on_pb_log_Clear_clicked();

    void on_pb_res_ok_clicked();

    void on_pb_res_clear_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
