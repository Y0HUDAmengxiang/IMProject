#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QTime>
#include <QDebug>

ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent),m_id(-1),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::setDialogInfo(QString ip,int id)
{
    //udp 保存ip ，tcp保存id
    m_ip =ip;
    m_id =id;
    //设置到窗口上
    setWindowTitle(QString("[%1]").arg(m_ip));
}

void ChatDialog::setChatContent(QString content)
{
    ui->tb_chat->append(QString("[%1] %2").arg(m_ip).arg(QTime::currentTime().toString("hh::mm::ss")));
    //发送聊天内容到Kerbel，发送给对端
    ui->tb_chat->append(content);
}

void ChatDialog::on_pb_send_clicked()
{
    //获取用户输入的纯文本
    QString content = ui->te_chat->toPlainText();
    //判断输入的是否合法是否是空或者是全空格
    if(content.isEmpty()||content.remove(" ").isEmpty()){
        ui->te_chat->clear();
        return;
    }
    //获取带格式的文本
    content = ui->te_chat->toHtml();
    //把编辑窗口的文本清空
    ui->te_chat->clear();
    //显示到浏览窗口上
    ui->tb_chat->append(QString("[me] %1").arg(QTime::currentTime().toString("hh::mm::ss")));
    //发送聊天内容到Kerbel，发送给对端
    ui->tb_chat->append(content);
    if(m_id>=0){
        //id》=0 就是Tcp
        Q_EMIT SIG_sendTcpContent(content,m_id);
        qDebug()<<"m_id:"<<m_id;
    }
    else
    {
    Q_EMIT SIG_sendContent(content,m_ip);
    }
}
