/****************************************************************************
** Meta object code from reading C++ file 'couchdbdatabase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modules/couchdb/couchdbdatabase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'couchdbdatabase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CouchDBDatabase_t {
    QByteArrayData data[13];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CouchDBDatabase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CouchDBDatabase_t qt_meta_stringdata_CouchDBDatabase = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CouchDBDatabase"
QT_MOC_LITERAL(1, 16, 15), // "hostnameChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "hostname"
QT_MOC_LITERAL(4, 42, 15), // "databaseChanged"
QT_MOC_LITERAL(5, 58, 8), // "database"
QT_MOC_LITERAL(6, 67, 10), // "urlChanged"
QT_MOC_LITERAL(7, 78, 3), // "url"
QT_MOC_LITERAL(8, 82, 16), // "availableChanged"
QT_MOC_LITERAL(9, 99, 9), // "available"
QT_MOC_LITERAL(10, 109, 7), // "compact"
QT_MOC_LITERAL(11, 117, 9), // "parameter"
QT_MOC_LITERAL(12, 127, 16) // "QQmlPropertyMap*"

    },
    "CouchDBDatabase\0hostnameChanged\0\0"
    "hostname\0databaseChanged\0database\0"
    "urlChanged\0url\0availableChanged\0"
    "available\0compact\0parameter\0"
    "QQmlPropertyMap*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CouchDBDatabase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       8,    1,   48,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      10,    0,   51,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Bool,    9,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::Bool, 0x00495001,
       3, QMetaType::QString, 0x00495103,
       5, QMetaType::QString, 0x00495103,
       7, QMetaType::QString, 0x00495001,
      11, 0x80000000 | 12, 0x00095409,

 // properties: notify_signal_id
       3,
       0,
       1,
       2,
       0,

       0        // eod
};

void CouchDBDatabase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CouchDBDatabase *_t = static_cast<CouchDBDatabase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hostnameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->databaseChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->urlChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->availableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->compact(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CouchDBDatabase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDatabase::hostnameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CouchDBDatabase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDatabase::databaseChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CouchDBDatabase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDatabase::urlChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CouchDBDatabase::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDatabase::availableChanged)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlPropertyMap* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CouchDBDatabase *_t = static_cast<CouchDBDatabase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->available(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->hostname(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->database(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->url(); break;
        case 4: *reinterpret_cast< QQmlPropertyMap**>(_v) = _t->parameter(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CouchDBDatabase *_t = static_cast<CouchDBDatabase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setHostname(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setDatabase(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CouchDBDatabase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CouchDBDatabase.data,
      qt_meta_data_CouchDBDatabase,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CouchDBDatabase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CouchDBDatabase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CouchDBDatabase.stringdata0))
        return static_cast<void*>(const_cast< CouchDBDatabase*>(this));
    return QObject::qt_metacast(_clname);
}

int CouchDBDatabase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CouchDBDatabase::hostnameChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CouchDBDatabase::databaseChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CouchDBDatabase::urlChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CouchDBDatabase::availableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
