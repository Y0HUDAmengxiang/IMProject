#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    //忽略关闭时间，不执行父类的关闭事件
    event->ignore();
    //弹出提示框确认用户是否关闭
    if(QMessageBox::Yes == QMessageBox::question(this,"message","Are you sure?")){
        //通知kernel，关闭用用程序，回收资源
        Q_EMIT SIG_closeDialog();
    }
}

void LoginDialog::on_pb_log_Ok_clicked()
{
    QString tel = ui->le_log_Tel->text();
    QString password = ui->le_log_PassWord->text();
    QString telTmp = tel;
    QString passwordTmp=password;
    //检测字符串是否为空
    if(tel.isEmpty()||password.isEmpty()||telTmp.remove(" ").isEmpty()||passwordTmp.remove(" ").isEmpty()){
        QMessageBox::about(this,"message","input invalid");
        return;
    }

    if(tel.length()!= 11||password.length()>15){
        QMessageBox::about(this,"message","input so long");
        return;
    }
    Q_EMIT SIG_logingCommit(tel,password);
    ui->le_log_Tel->setText("");
    ui->le_log_PassWord->setText("");
}

void LoginDialog::on_pb_log_Clear_clicked()
{
    ui->le_log_Tel->setText("");
    ui->le_log_PassWord->setText("");
}

void LoginDialog::on_pb_res_ok_clicked()
{
    //1.从空间上获取信息
    QString  name =ui->le_res_nickname->text();
    QString  tel = ui->le_res_tel->text();
    QString password = ui->le_res_password->text();
    QString nameTmp = name;
    QString telTmp = tel;
    QString passwordTmp=password;
    //2.校验用户数据是否合法
    //2.1校验字符串是否为空，或者是空格
    if(name.isEmpty()||tel.isEmpty()||password.isEmpty()||nameTmp.remove(" ").isEmpty()||telTmp.remove(" ").isEmpty()||passwordTmp.remove(" ").isEmpty()){
        QMessageBox::about(this,"message","input invalid");
        return;
    }
    //2.2校验字符串长度
    if(name.length()>10||tel.length()!= 11||password.length()>15){
        QMessageBox::about(this,"message","input so long");
        return;
    }
    //2.3校验参数是否合法(例如；昵称不准有特殊字符，电话号必须是数字)

    //3.把数据发送给Kernel
    Q_EMIT SIG_resgisterCommit(name,tel,password);
    ui->le_res_tel->setText("");
    ui->le_res_password->setText("");
    ui->le_res_nickname->setText("");
}

void LoginDialog::on_pb_res_clear_clicked()
{
    ui->le_res_tel->setText("");
    ui->le_res_password->setText("");
    ui->le_res_nickname->setText("");
}
