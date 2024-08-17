/********************************************************************************
** Form generated from reading UI file 'imclientdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMCLIENTDIALOG_H
#define UI_IMCLIENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IMClientDialog
{
public:
    QPushButton *pb_icon;
    QLabel *lb_name;
    QLineEdit *le_feeling;
    QTabWidget *tb_page;
    QWidget *tb_friend;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_list_Tcp;
    QSpacerItem *verticalSpacer_2;
    QWidget *tb_tpfriend;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *wdg_list;
    QSpacerItem *verticalSpacer;
    QWidget *tb_group;
    QPushButton *pb_tools_1;
    QPushButton *pb_tools_2;
    QPushButton *pb_tools_3;
    QPushButton *pb_tools_4;

    void setupUi(QDialog *IMClientDialog)
    {
        if (IMClientDialog->objectName().isEmpty())
            IMClientDialog->setObjectName(QString::fromUtf8("IMClientDialog"));
        IMClientDialog->resize(300, 650);
        pb_icon = new QPushButton(IMClientDialog);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(0, 0, 61, 61));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tx/9.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_icon->setIcon(icon);
        pb_icon->setIconSize(QSize(60, 60));
        pb_icon->setFlat(true);
        lb_name = new QLabel(IMClientDialog);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(70, 10, 181, 21));
        le_feeling = new QLineEdit(IMClientDialog);
        le_feeling->setObjectName(QString::fromUtf8("le_feeling"));
        le_feeling->setGeometry(QRect(70, 40, 201, 21));
        tb_page = new QTabWidget(IMClientDialog);
        tb_page->setObjectName(QString::fromUtf8("tb_page"));
        tb_page->setGeometry(QRect(0, 80, 301, 521));
        tb_friend = new QWidget();
        tb_friend->setObjectName(QString::fromUtf8("tb_friend"));
        scrollArea_2 = new QScrollArea(tb_friend);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(0, 0, 291, 491));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 289, 489));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 5, 0, 5);
        wdg_list_Tcp = new QWidget(scrollAreaWidgetContents_2);
        wdg_list_Tcp->setObjectName(QString::fromUtf8("wdg_list_Tcp"));

        verticalLayout_2->addWidget(wdg_list_Tcp);

        verticalSpacer_2 = new QSpacerItem(20, 460, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        tb_page->addTab(tb_friend, QString());
        tb_tpfriend = new QWidget();
        tb_tpfriend->setObjectName(QString::fromUtf8("tb_tpfriend"));
        scrollArea = new QScrollArea(tb_tpfriend);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 291, 491));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 289, 489));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 0, 5, 0);
        wdg_list = new QWidget(scrollAreaWidgetContents);
        wdg_list->setObjectName(QString::fromUtf8("wdg_list"));

        verticalLayout->addWidget(wdg_list);

        verticalSpacer = new QSpacerItem(20, 470, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);
        tb_page->addTab(tb_tpfriend, QString());
        tb_group = new QWidget();
        tb_group->setObjectName(QString::fromUtf8("tb_group"));
        tb_page->addTab(tb_group, QString());
        pb_tools_1 = new QPushButton(IMClientDialog);
        pb_tools_1->setObjectName(QString::fromUtf8("pb_tools_1"));
        pb_tools_1->setGeometry(QRect(10, 610, 31, 31));
        pb_tools_2 = new QPushButton(IMClientDialog);
        pb_tools_2->setObjectName(QString::fromUtf8("pb_tools_2"));
        pb_tools_2->setGeometry(QRect(180, 610, 31, 31));
        pb_tools_3 = new QPushButton(IMClientDialog);
        pb_tools_3->setObjectName(QString::fromUtf8("pb_tools_3"));
        pb_tools_3->setGeometry(QRect(220, 610, 31, 31));
        pb_tools_4 = new QPushButton(IMClientDialog);
        pb_tools_4->setObjectName(QString::fromUtf8("pb_tools_4"));
        pb_tools_4->setGeometry(QRect(260, 610, 31, 31));

        retranslateUi(IMClientDialog);

        tb_page->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(IMClientDialog);
    } // setupUi

    void retranslateUi(QDialog *IMClientDialog)
    {
        IMClientDialog->setWindowTitle(QApplication::translate("IMClientDialog", "IMClientDialog", nullptr));
        pb_icon->setText(QString());
        lb_name->setText(QApplication::translate("IMClientDialog", "\350\214\203\345\256\207\350\210\252", nullptr));
        le_feeling->setText(QApplication::translate("IMClientDialog", "\347\211\233\351\200\274", nullptr));
        tb_page->setTabText(tb_page->indexOf(tb_friend), QApplication::translate("IMClientDialog", "\350\201\224\347\263\273\344\272\272", nullptr));
        tb_page->setTabText(tb_page->indexOf(tb_tpfriend), QApplication::translate("IMClientDialog", "\344\270\264\346\227\266\345\245\275\345\217\213", nullptr));
        tb_page->setTabText(tb_page->indexOf(tb_group), QApplication::translate("IMClientDialog", "\347\276\244\347\273\204", nullptr));
        pb_tools_1->setText(QString());
        pb_tools_2->setText(QString());
        pb_tools_3->setText(QString());
        pb_tools_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IMClientDialog: public Ui_IMClientDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMCLIENTDIALOG_H
