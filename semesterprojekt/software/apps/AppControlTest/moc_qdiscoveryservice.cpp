/****************************************************************************
** Meta object code from reading C++ file 'qdiscoveryservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modules/qdiscoveryservice/qdiscoveryservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdiscoveryservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QDiscoveryService_t {
    QByteArrayData data[13];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDiscoveryService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDiscoveryService_t qt_meta_stringdata_QDiscoveryService = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QDiscoveryService"
QT_MOC_LITERAL(1, 18, 18), // "serviceNameChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 11), // "serviceName"
QT_MOC_LITERAL(4, 50, 18), // "serviceInfoChanged"
QT_MOC_LITERAL(5, 69, 11), // "serviceInfo"
QT_MOC_LITERAL(6, 81, 22), // "discoveryActiveChanged"
QT_MOC_LITERAL(7, 104, 22), // "loopbackEnabledChanged"
QT_MOC_LITERAL(8, 127, 14), // "startDiscovery"
QT_MOC_LITERAL(9, 142, 13), // "stopDiscovery"
QT_MOC_LITERAL(10, 156, 18), // "publishServiceInfo"
QT_MOC_LITERAL(11, 175, 15), // "discoveryActive"
QT_MOC_LITERAL(12, 191, 15) // "loopbackEnabled"

    },
    "QDiscoveryService\0serviceNameChanged\0"
    "\0serviceName\0serviceInfoChanged\0"
    "serviceInfo\0discoveryActiveChanged\0"
    "loopbackEnabledChanged\0startDiscovery\0"
    "stopDiscovery\0publishServiceInfo\0"
    "discoveryActive\0loopbackEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDiscoveryService[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       4,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,
       7,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00495103,
       5, QMetaType::QJsonObject, 0x00495103,
      11, QMetaType::Bool, 0x00495103,
      12, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void QDiscoveryService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QDiscoveryService *_t = static_cast<QDiscoveryService *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serviceNameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->serviceInfoChanged((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 2: _t->discoveryActiveChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->loopbackEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->startDiscovery(); break;
        case 5: _t->stopDiscovery(); break;
        case 6: _t->publishServiceInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QDiscoveryService::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QDiscoveryService::serviceNameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QDiscoveryService::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QDiscoveryService::serviceInfoChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QDiscoveryService::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QDiscoveryService::discoveryActiveChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QDiscoveryService::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QDiscoveryService::loopbackEnabledChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QDiscoveryService *_t = static_cast<QDiscoveryService *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->serviceName(); break;
        case 1: *reinterpret_cast< QJsonObject*>(_v) = _t->serviceInfo(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isDiscoveryActive(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isLoopbackEnabled(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        QDiscoveryService *_t = static_cast<QDiscoveryService *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setServiceName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setServiceInfo(*reinterpret_cast< QJsonObject*>(_v)); break;
        case 2: _t->setDiscoveryActive(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setLoopbackEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QDiscoveryService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QDiscoveryService.data,
      qt_meta_data_QDiscoveryService,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QDiscoveryService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDiscoveryService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QDiscoveryService.stringdata0))
        return static_cast<void*>(const_cast< QDiscoveryService*>(this));
    return QObject::qt_metacast(_clname);
}

int QDiscoveryService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QDiscoveryService::serviceNameChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QDiscoveryService::serviceInfoChanged(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QDiscoveryService::discoveryActiveChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QDiscoveryService::loopbackEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
