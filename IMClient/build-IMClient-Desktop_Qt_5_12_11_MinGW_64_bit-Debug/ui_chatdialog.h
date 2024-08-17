/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QGroupBox *groupBox;
    QPushButton *pb_tool1;
    QPushButton *pb_tool2;
    QPushButton *pushButton_3;
    QTextBrowser *tb_chat;
    QTextEdit *te_chat;
    QPushButton *pb_send;

    void setupUi(QWidget *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QString::fromUtf8("ChatDialog"));
        ChatDialog->resize(494, 385);
        groupBox = new QGroupBox(ChatDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 230, 121, 41));
        pb_tool1 = new QPushButton(groupBox);
        pb_tool1->setObjectName(QString::fromUtf8("pb_tool1"));
        pb_tool1->setGeometry(QRect(10, 10, 20, 21));
        pb_tool2 = new QPushButton(groupBox);
        pb_tool2->setObjectName(QString::fromUtf8("pb_tool2"));
        pb_tool2->setGeometry(QRect(50, 10, 20, 21));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(90, 10, 20, 21));
        tb_chat = new QTextBrowser(ChatDialog);
        tb_chat->setObjectName(QString::fromUtf8("tb_chat"));
        tb_chat->setGeometry(QRect(0, 0, 411, 221));
        te_chat = new QTextEdit(ChatDialog);
        te_chat->setObjectName(QString::fromUtf8("te_chat"));
        te_chat->setGeometry(QRect(0, 280, 411, 81));
        pb_send = new QPushButton(ChatDialog);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));
        pb_send->setGeometry(QRect(420, 360, 75, 23));

        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QWidget *ChatDialog)
    {
        ChatDialog->setWindowTitle(QApplication::translate("ChatDialog", "Form", nullptr));
        groupBox->setTitle(QString());
        pb_tool1->setText(QString());
        pb_tool2->setText(QString());
        pushButton_3->setText(QString());
        pb_send->setText(QApplication::translate("ChatDialog", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
