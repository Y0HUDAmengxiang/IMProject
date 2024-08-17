#-------------------------------------------------
#
# Project created by QtCreator 2023-07-30T13:31:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = IMClient
#TARGET = untitled
TEMPLATE = app
INCLUDEPATH += ./INet
INCLUDEPATH += ./INetMediator
INCLUDEPATH += ./config

LIBS += -lWs2_32

SOURCES += main.cpp\
        imclientdialog.cpp \
    INet/TcpNetClient.cpp \
    INet/UdpNet.cpp \
    INetMediator/TcpNetClientMediator.cpp \
    INetMediator/UdpNetMediator.cpp \
    ckernel.cpp \
    INetMediator/INetMediator.cpp \
    useritem.cpp \
    chatdialog.cpp \
    logindialog.cpp

HEADERS  += imclientdialog.h \
    config/config.h \
    INet/INet.h \
    INet/TcpNetClient.h \
    INet/UdpNet.h \
    INetMediator/INetMediator.h \
    INetMediator/TcpNetClientMediator.h \
    INetMediator/UdpNetMediator.h \
    ckernel.h \
    useritem.h \
    chatdialog.h \
    logindialog.h

FORMS    += imclientdialog.ui \
    useritem.ui \
    chatdialog.ui \
    logindialog.ui

RESOURCES += \
    Resource.qrc
