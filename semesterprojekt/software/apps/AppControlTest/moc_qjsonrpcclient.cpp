/****************************************************************************
** Meta object code from reading C++ file 'qjsonrpcclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modules/qjsonrpc/qjsonrpcclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qjsonrpcclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QJsonRpcClient_t {
    QByteArrayData data[21];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QJsonRpcClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QJsonRpcClient_t qt_meta_stringdata_QJsonRpcClient = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QJsonRpcClient"
QT_MOC_LITERAL(1, 15, 20), // "notificationReceived"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "methodName"
QT_MOC_LITERAL(4, 48, 6), // "params"
QT_MOC_LITERAL(5, 55, 14), // "resultReceived"
QT_MOC_LITERAL(6, 70, 6), // "result"
QT_MOC_LITERAL(7, 77, 2), // "id"
QT_MOC_LITERAL(8, 80, 13), // "errorReceived"
QT_MOC_LITERAL(9, 94, 11), // "errorObject"
QT_MOC_LITERAL(10, 106, 16), // "connectedChanged"
QT_MOC_LITERAL(11, 123, 13), // "binaryChanged"
QT_MOC_LITERAL(12, 137, 12), // "asyncChanged"
QT_MOC_LITERAL(13, 150, 11), // "sendMessage"
QT_MOC_LITERAL(14, 162, 13), // "messageObject"
QT_MOC_LITERAL(15, 176, 20), // "onNewMessageReceived"
QT_MOC_LITERAL(16, 197, 10), // "callMethod"
QT_MOC_LITERAL(17, 208, 7), // "timeout"
QT_MOC_LITERAL(18, 216, 4), // "open"
QT_MOC_LITERAL(19, 221, 10), // "serverName"
QT_MOC_LITERAL(20, 232, 5) // "close"

    },
    "QJsonRpcClient\0notificationReceived\0"
    "\0methodName\0params\0resultReceived\0"
    "result\0id\0errorReceived\0errorObject\0"
    "connectedChanged\0binaryChanged\0"
    "asyncChanged\0sendMessage\0messageObject\0"
    "onNewMessageReceived\0callMethod\0timeout\0"
    "open\0serverName\0close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QJsonRpcClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       5,    3,   84,    2, 0x06 /* Public */,
       8,    3,   91,    2, 0x06 /* Public */,
      10,    1,   98,    2, 0x06 /* Public */,
      11,    1,  101,    2, 0x06 /* Public */,
      12,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  107,    2, 0x09 /* Protected */,
      15,    1,  110,    2, 0x09 /* Protected */,
      16,    3,  113,    2, 0x0a /* Public */,
      16,    2,  120,    2, 0x2a /* Public | MethodCloned */,
      18,    1,  125,    2, 0x0a /* Public */,
      18,    0,  128,    2, 0x2a /* Public | MethodCloned */,
      20,    0,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonValue,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonValue, QMetaType::QString,    3,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QString,    3,    9,    7,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonObject,   14,
    QMetaType::Void, QMetaType::QJsonObject,   14,
    QMetaType::QJsonValue, QMetaType::QString, QMetaType::QJsonValue, QMetaType::Int,    3,    4,   17,
    QMetaType::QJsonValue, QMetaType::QString, QMetaType::QJsonValue,    3,    4,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QJsonRpcClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QJsonRpcClient *_t = static_cast<QJsonRpcClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notificationReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonValue(*)>(_a[2]))); break;
        case 1: _t->resultReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonValue(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->errorReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->connectedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->binaryChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->asyncChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->sendMessage((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 7: _t->onNewMessageReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 8: { QJsonValue _r = _t->callMethod((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QJsonValue(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = std::move(_r); }  break;
        case 9: { QJsonValue _r = _t->callMethod((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QJsonValue(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->open(); break;
        case 12: _t->close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QJsonRpcClient::*_t)(QString , QJsonValue );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QJsonRpcClient::notificationReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QJsonRpcClient::*_t)(QString , QJsonValue , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QJsonRpcClient::resultReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QJsonRpcClient::*_t)(QString , QJsonObject , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QJsonRpcClient::errorReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QJsonRpcClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QJsonRpcClient::connectedChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QJsonRpcClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QJsonRpcClient::binaryChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QJsonRpcClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QJsonRpcClient::asyncChanged)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject QJsonRpcClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QJsonRpcClient.data,
      qt_meta_data_QJsonRpcClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QJsonRpcClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QJsonRpcClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QJsonRpcClient.stringdata0))
        return static_cast<void*>(const_cast< QJsonRpcClient*>(this));
    return QObject::qt_metacast(_clname);
}

int QJsonRpcClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QJsonRpcClient::notificationReceived(QString _t1, QJsonValue _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QJsonRpcClient::resultReceived(QString _t1, QJsonValue _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QJsonRpcClient::errorReceived(QString _t1, QJsonObject _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QJsonRpcClient::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QJsonRpcClient::binaryChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QJsonRpcClient::asyncChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
