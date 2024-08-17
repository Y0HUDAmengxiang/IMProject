/****************************************************************************
** Meta object code from reading C++ file 'ckernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../IMClient/ckernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ckernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CKernel_t {
    QByteArrayData data[22];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CKernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CKernel_t qt_meta_stringdata_CKernel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CKernel"
QT_MOC_LITERAL(1, 8, 14), // "slot_ReadyData"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "lSend"
QT_MOC_LITERAL(4, 30, 5), // "char*"
QT_MOC_LITERAL(5, 36, 7), // "recvBuf"
QT_MOC_LITERAL(6, 44, 4), // "nLen"
QT_MOC_LITERAL(7, 49, 15), // "slot_showhatDlg"
QT_MOC_LITERAL(8, 65, 2), // "ip"
QT_MOC_LITERAL(9, 68, 16), // "slot_sendContent"
QT_MOC_LITERAL(10, 85, 7), // "content"
QT_MOC_LITERAL(11, 93, 19), // "slot_sendTcpContent"
QT_MOC_LITERAL(12, 113, 2), // "id"
QT_MOC_LITERAL(13, 116, 13), // "slot_closeApp"
QT_MOC_LITERAL(14, 130, 19), // "slot_registerCommit"
QT_MOC_LITERAL(15, 150, 4), // "name"
QT_MOC_LITERAL(16, 155, 3), // "tel"
QT_MOC_LITERAL(17, 159, 8), // "password"
QT_MOC_LITERAL(18, 168, 17), // "slot_LogingCommit"
QT_MOC_LITERAL(19, 186, 19), // "slot_showChatTcpDlg"
QT_MOC_LITERAL(20, 206, 16), // "slot_closeDialog"
QT_MOC_LITERAL(21, 223, 14) // "slot_addFriend"

    },
    "CKernel\0slot_ReadyData\0\0lSend\0char*\0"
    "recvBuf\0nLen\0slot_showhatDlg\0ip\0"
    "slot_sendContent\0content\0slot_sendTcpContent\0"
    "id\0slot_closeApp\0slot_registerCommit\0"
    "name\0tel\0password\0slot_LogingCommit\0"
    "slot_showChatTcpDlg\0slot_closeDialog\0"
    "slot_addFriend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CKernel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   64,    2, 0x0a /* Public */,
       7,    1,   71,    2, 0x0a /* Public */,
       9,    2,   74,    2, 0x0a /* Public */,
      11,    2,   79,    2, 0x0a /* Public */,
      13,    0,   84,    2, 0x0a /* Public */,
      14,    3,   85,    2, 0x0a /* Public */,
      18,    2,   92,    2, 0x0a /* Public */,
      19,    1,   97,    2, 0x0a /* Public */,
      20,    0,  100,    2, 0x0a /* Public */,
      21,    0,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Long, 0x80000000 | 4, QMetaType::Int,    3,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   16,   17,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CKernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CKernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_ReadyData((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->slot_showhatDlg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slot_sendContent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->slot_sendTcpContent((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_closeApp(); break;
        case 5: _t->slot_registerCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->slot_LogingCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->slot_showChatTcpDlg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_closeDialog(); break;
        case 9: _t->slot_addFriend(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CKernel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CKernel.data,
    qt_meta_data_CKernel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CKernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CKernel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CKernel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CKernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
