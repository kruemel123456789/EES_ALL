/****************************************************************************
** Meta object code from reading C++ file 'couchdbview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modules/couchdb/couchdbview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'couchdbview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CouchDBView_t {
    QByteArrayData data[25];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CouchDBView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CouchDBView_t qt_meta_stringdata_CouchDBView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CouchDBView"
QT_MOC_LITERAL(1, 12, 15), // "databaseChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "CouchDBDatabase*"
QT_MOC_LITERAL(4, 46, 8), // "database"
QT_MOC_LITERAL(5, 55, 16), // "designDocChanged"
QT_MOC_LITERAL(6, 72, 9), // "designDoc"
QT_MOC_LITERAL(7, 82, 11), // "viewChanged"
QT_MOC_LITERAL(8, 94, 4), // "view"
QT_MOC_LITERAL(9, 99, 10), // "keyChanged"
QT_MOC_LITERAL(10, 110, 3), // "key"
QT_MOC_LITERAL(11, 114, 15), // "startKeyChanged"
QT_MOC_LITERAL(12, 130, 8), // "startKey"
QT_MOC_LITERAL(13, 139, 13), // "endKeyChanged"
QT_MOC_LITERAL(14, 153, 6), // "endKey"
QT_MOC_LITERAL(15, 160, 11), // "rowsChanged"
QT_MOC_LITERAL(16, 172, 4), // "rows"
QT_MOC_LITERAL(17, 177, 4), // "load"
QT_MOC_LITERAL(18, 182, 6), // "setDoc"
QT_MOC_LITERAL(19, 189, 4), // "json"
QT_MOC_LITERAL(20, 194, 5), // "getId"
QT_MOC_LITERAL(21, 200, 1), // "i"
QT_MOC_LITERAL(22, 202, 6), // "getKey"
QT_MOC_LITERAL(23, 209, 8), // "getValue"
QT_MOC_LITERAL(24, 218, 8) // "rowCount"

    },
    "CouchDBView\0databaseChanged\0\0"
    "CouchDBDatabase*\0database\0designDocChanged\0"
    "designDoc\0viewChanged\0view\0keyChanged\0"
    "key\0startKeyChanged\0startKey\0endKeyChanged\0"
    "endKey\0rowsChanged\0rows\0load\0setDoc\0"
    "json\0getId\0i\0getKey\0getValue\0rowCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CouchDBView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       8,  108, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       7,    1,   80,    2, 0x06 /* Public */,
       9,    1,   83,    2, 0x06 /* Public */,
      11,    1,   86,    2, 0x06 /* Public */,
      13,    1,   89,    2, 0x06 /* Public */,
      15,    1,   92,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      17,    0,   95,    2, 0x02 /* Public */,
      18,    1,   96,    2, 0x02 /* Public */,
      20,    1,   99,    2, 0x02 /* Public */,
      22,    1,  102,    2, 0x02 /* Public */,
      23,    1,  105,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QVariant,   10,
    QMetaType::Void, QMetaType::QVariant,   12,
    QMetaType::Void, QMetaType::QVariant,   14,
    QMetaType::Void, QMetaType::QJsonArray,   16,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   19,
    QMetaType::QString, QMetaType::Int,   21,
    QMetaType::QJsonValue, QMetaType::Int,   21,
    QMetaType::QJsonValue, QMetaType::Int,   21,

 // properties: name, type, flags
       4, 0x80000000 | 3, 0x0049510b,
      16, QMetaType::QJsonArray, 0x00495001,
      24, QMetaType::Int, 0x00495001,
       6, QMetaType::QString, 0x00495103,
       8, QMetaType::QString, 0x00495103,
      10, QMetaType::QVariant, 0x00495103,
      12, QMetaType::QVariant, 0x00495103,
      14, QMetaType::QVariant, 0x00495103,

 // properties: notify_signal_id
       0,
       6,
       6,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void CouchDBView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CouchDBView *_t = static_cast<CouchDBView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->databaseChanged((*reinterpret_cast< CouchDBDatabase*(*)>(_a[1]))); break;
        case 1: _t->designDocChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->viewChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->keyChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 4: _t->startKeyChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->endKeyChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 6: _t->rowsChanged((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 7: _t->load(); break;
        case 8: _t->setDoc((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 9: { QString _r = _t->getId((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QJsonValue _r = _t->getKey((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = std::move(_r); }  break;
        case 11: { QJsonValue _r = _t->getValue((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = std::move(_r); }  break;
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
            typedef void (CouchDBView::*_t)(CouchDBDatabase * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::databaseChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CouchDBView::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::designDocChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CouchDBView::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::viewChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CouchDBView::*_t)(QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::keyChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CouchDBView::*_t)(QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::startKeyChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CouchDBView::*_t)(QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::endKeyChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CouchDBView::*_t)(QJsonArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBView::rowsChanged)) {
                *result = 6;
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
        CouchDBView *_t = static_cast<CouchDBView *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< CouchDBDatabase**>(_v) = _t->database(); break;
        case 1: *reinterpret_cast< QJsonArray*>(_v) = _t->rows(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->rowCount(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->designDoc(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->view(); break;
        case 5: *reinterpret_cast< QVariant*>(_v) = _t->key(); break;
        case 6: *reinterpret_cast< QVariant*>(_v) = _t->startKey(); break;
        case 7: *reinterpret_cast< QVariant*>(_v) = _t->endKey(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CouchDBView *_t = static_cast<CouchDBView *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDatabase(*reinterpret_cast< CouchDBDatabase**>(_v)); break;
        case 3: _t->setDesignDoc(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setView(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setKey(*reinterpret_cast< QVariant*>(_v)); break;
        case 6: _t->setStartKey(*reinterpret_cast< QVariant*>(_v)); break;
        case 7: _t->setEndKey(*reinterpret_cast< QVariant*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CouchDBView::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CouchDBView.data,
      qt_meta_data_CouchDBView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CouchDBView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CouchDBView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CouchDBView.stringdata0))
        return static_cast<void*>(const_cast< CouchDBView*>(this));
    return QObject::qt_metacast(_clname);
}

int CouchDBView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CouchDBView::databaseChanged(CouchDBDatabase * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CouchDBView::designDocChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CouchDBView::viewChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CouchDBView::keyChanged(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CouchDBView::startKeyChanged(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CouchDBView::endKeyChanged(QVariant _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CouchDBView::rowsChanged(QJsonArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
