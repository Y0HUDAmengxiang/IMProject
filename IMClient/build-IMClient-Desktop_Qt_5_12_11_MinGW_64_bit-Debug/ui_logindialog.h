/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tb_loging;
    QLabel *lb_logTel;
    QLabel *lb_log_PassWord;
    QLineEdit *le_log_Tel;
    QLineEdit *le_log_PassWord;
    QPushButton *pb_log_Ok;
    QPushButton *pb_log_Clear;
    QWidget *widget;
    QLabel *lb_res_tel;
    QLabel *lb_res_nickname;
    QLabel *lb_res_password;
    QPushButton *pb_res_ok;
    QPushButton *pb_res_clear;
    QLineEdit *le_res_tel;
    QLineEdit *le_res_nickname;
    QLineEdit *le_res_password;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(625, 532);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 291, 531));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/icon2.png")));
        label->setScaledContents(true);
        tabWidget = new QTabWidget(LoginDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(290, 0, 341, 531));
        tb_loging = new QWidget();
        tb_loging->setObjectName(QString::fromUtf8("tb_loging"));
        lb_logTel = new QLabel(tb_loging);
        lb_logTel->setObjectName(QString::fromUtf8("lb_logTel"));
        lb_logTel->setGeometry(QRect(10, 60, 81, 31));
        lb_log_PassWord = new QLabel(tb_loging);
        lb_log_PassWord->setObjectName(QString::fromUtf8("lb_log_PassWord"));
        lb_log_PassWord->setGeometry(QRect(10, 130, 81, 31));
        le_log_Tel = new QLineEdit(tb_loging);
        le_log_Tel->setObjectName(QString::fromUtf8("le_log_Tel"));
        le_log_Tel->setGeometry(QRect(100, 60, 201, 31));
        le_log_PassWord = new QLineEdit(tb_loging);
        le_log_PassWord->setObjectName(QString::fromUtf8("le_log_PassWord"));
        le_log_PassWord->setGeometry(QRect(100, 130, 201, 31));
        le_log_PassWord->setEchoMode(QLineEdit::Password);
        pb_log_Ok = new QPushButton(tb_loging);
        pb_log_Ok->setObjectName(QString::fromUtf8("pb_log_Ok"));
        pb_log_Ok->setGeometry(QRect(10, 350, 91, 41));
        pb_log_Clear = new QPushButton(tb_loging);
        pb_log_Clear->setObjectName(QString::fromUtf8("pb_log_Clear"));
        pb_log_Clear->setGeometry(QRect(180, 350, 91, 41));
        tabWidget->addTab(tb_loging, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        lb_res_tel = new QLabel(widget);
        lb_res_tel->setObjectName(QString::fromUtf8("lb_res_tel"));
        lb_res_tel->setGeometry(QRect(10, 50, 71, 21));
        lb_res_nickname = new QLabel(widget);
        lb_res_nickname->setObjectName(QString::fromUtf8("lb_res_nickname"));
        lb_res_nickname->setGeometry(QRect(10, 120, 71, 21));
        lb_res_password = new QLabel(widget);
        lb_res_password->setObjectName(QString::fromUtf8("lb_res_password"));
        lb_res_password->setGeometry(QRect(10, 180, 71, 21));
        pb_res_ok = new QPushButton(widget);
        pb_res_ok->setObjectName(QString::fromUtf8("pb_res_ok"));
        pb_res_ok->setGeometry(QRect(10, 350, 71, 31));
        pb_res_clear = new QPushButton(widget);
        pb_res_clear->setObjectName(QString::fromUtf8("pb_res_clear"));
        pb_res_clear->setGeometry(QRect(150, 350, 71, 31));
        le_res_tel = new QLineEdit(widget);
        le_res_tel->setObjectName(QString::fromUtf8("le_res_tel"));
        le_res_tel->setGeometry(QRect(100, 50, 201, 31));
        le_res_nickname = new QLineEdit(widget);
        le_res_nickname->setObjectName(QString::fromUtf8("le_res_nickname"));
        le_res_nickname->setGeometry(QRect(100, 110, 201, 31));
        le_res_password = new QLineEdit(widget);
        le_res_password->setObjectName(QString::fromUtf8("le_res_password"));
        le_res_password->setGeometry(QRect(100, 180, 201, 31));
        le_res_password->setEchoMode(QLineEdit::Password);
        tabWidget->addTab(widget, QString());

        retranslateUi(LoginDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QString());
        lb_logTel->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
        lb_log_PassWord->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
#ifndef QT_NO_TOOLTIP
        le_log_Tel->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\346\211\213\346\234\272\345\217\267\345\277\205\351\241\273\346\230\25711\344\275\215\344\270\224\346\230\257\346\225\260\345\255\227</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_log_PassWord->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\351\225\277\345\272\246\345\277\205\351\241\273\346\230\25715\357\274\214\344\270\224\346\230\257\345\255\227\346\257\215\346\225\260\345\255\227\344\270\213\345\210\222\347\272\277</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_log_Ok->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
        pb_log_Clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tb_loging), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        lb_res_tel->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
        lb_res_nickname->setText(QApplication::translate("LoginDialog", "\346\230\265\347\247\260\357\274\232", nullptr));
        lb_res_password->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        pb_res_ok->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", nullptr));
        pb_res_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", nullptr));
#ifndef QT_NO_TOOLTIP
        le_res_tel->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\346\211\213\346\234\272\345\217\267\345\277\205\351\241\273\346\230\25711\344\275\215\344\270\224\346\230\257\346\225\260\345\255\227</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_res_nickname->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\351\232\217\344\276\277\350\265\267\350\266\212\346\212\275\350\261\241\350\266\212\345\245\275</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_res_password->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\344\270\215\345\201\232\350\246\201\346\261\202\357\274\214\350\203\275\345\257\271\345\260\261\350\241\214</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("LoginDialog", " \346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
