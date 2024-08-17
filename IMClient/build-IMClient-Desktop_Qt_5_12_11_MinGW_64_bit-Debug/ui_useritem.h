/********************************************************************************
** Form generated from reading UI file 'useritem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERITEM_H
#define UI_USERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_useritem
{
public:
    QPushButton *pb_icon;
    QLabel *lb_name;
    QLabel *lb_feeling;

    void setupUi(QWidget *useritem)
    {
        if (useritem->objectName().isEmpty())
            useritem->setObjectName(QString::fromUtf8("useritem"));
        useritem->resize(290, 50);
        useritem->setMinimumSize(QSize(290, 50));
        useritem->setMaximumSize(QSize(290, 50));
        pb_icon = new QPushButton(useritem);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(0, 0, 41, 41));
        lb_name = new QLabel(useritem);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(60, 1, 151, 20));
        lb_feeling = new QLabel(useritem);
        lb_feeling->setObjectName(QString::fromUtf8("lb_feeling"));
        lb_feeling->setGeometry(QRect(60, 30, 131, 16));

        retranslateUi(useritem);

        QMetaObject::connectSlotsByName(useritem);
    } // setupUi

    void retranslateUi(QWidget *useritem)
    {
        useritem->setWindowTitle(QApplication::translate("useritem", "Form", nullptr));
        pb_icon->setText(QString());
        lb_name->setText(QApplication::translate("useritem", "\347\216\213\351\221\253\345\256\207", nullptr));
        lb_feeling->setText(QApplication::translate("useritem", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class useritem: public Ui_useritem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERITEM_H
