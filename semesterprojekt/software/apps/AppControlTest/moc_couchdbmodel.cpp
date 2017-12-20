/****************************************************************************
** Meta object code from reading C++ file 'couchdbmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modules/couchdb/couchdbmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'couchdbmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CouchDBModel_t {
    QByteArrayData data[12];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CouchDBModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CouchDBModel_t qt_meta_stringdata_CouchDBModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CouchDBModel"
QT_MOC_LITERAL(1, 13, 15), // "databaseChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "CouchDBDatabase*"
QT_MOC_LITERAL(4, 47, 8), // "database"
QT_MOC_LITERAL(5, 56, 16), // "designDocChanged"
QT_MOC_LITERAL(6, 73, 9), // "designDoc"
QT_MOC_LITERAL(7, 83, 15), // "viewNameChanged"
QT_MOC_LITERAL(8, 99, 8), // "viewName"
QT_MOC_LITERAL(9, 108, 4), // "load"
QT_MOC_LITERAL(10, 113, 6), // "setDoc"
QT_MOC_LITERAL(11, 120, 4) // "json"

    },
    "CouchDBModel\0databaseChanged\0\0"
    "CouchDBDatabase*\0database\0designDocChanged\0"
    "designDoc\0viewNameChanged\0viewName\0"
    "load\0setDoc\0json"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CouchDBModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       3,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       7,    1,   45,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    0,   48,    2, 0x02 /* Public */,
      10,    1,   49,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   11,

 // properties: name, type, flags
       4, 0x80000000 | 3, 0x0049510b,
       6, QMetaType::QString, 0x00495103,
       8, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void CouchDBModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CouchDBModel *_t = static_cast<CouchDBModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->databaseChanged((*reinterpret_cast< CouchDBDatabase*(*)>(_a[1]))); break;
        case 1: _t->designDocChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->viewNameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->load(); break;
        case 4: _t->setDoc((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CouchDBDatabase* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CouchDBModel::*_t)(CouchDBDatabase * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBModel::databaseChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CouchDBModel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBModel::designDocChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CouchDBModel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBModel::viewNameChanged)) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CouchDBDatabase* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CouchDBModel *_t = static_cast<CouchDBModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< CouchDBDatabase**>(_v) = _t->database(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->designDoc(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->viewName(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CouchDBModel *_t = static_cast<CouchDBModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDatabase(*reinterpret_cast< CouchDBDatabase**>(_v)); break;
        case 1: _t->setDesignDoc(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setViewName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CouchDBModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_CouchDBModel.data,
      qt_meta_data_CouchDBModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CouchDBModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CouchDBModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CouchDBModel.stringdata0))
        return static_cast<void*>(const_cast< CouchDBModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int CouchDBModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CouchDBModel::databaseChanged(CouchDBDatabase * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CouchDBModel::designDocChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CouchDBModel::viewNameChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
