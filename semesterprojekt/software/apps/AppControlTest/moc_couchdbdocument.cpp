/****************************************************************************
** Meta object code from reading C++ file 'couchdbdocument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../modules/couchdb/couchdbdocument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'couchdbdocument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CouchDBDocument_t {
    QByteArrayData data[26];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CouchDBDocument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CouchDBDocument_t qt_meta_stringdata_CouchDBDocument = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CouchDBDocument"
QT_MOC_LITERAL(1, 16, 15), // "databaseChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 16), // "CouchDBDatabase*"
QT_MOC_LITERAL(4, 50, 8), // "database"
QT_MOC_LITERAL(5, 59, 9), // "idChanged"
QT_MOC_LITERAL(6, 69, 2), // "id"
QT_MOC_LITERAL(7, 72, 10), // "revChanged"
QT_MOC_LITERAL(8, 83, 3), // "rev"
QT_MOC_LITERAL(9, 87, 18), // "attachmentsChanged"
QT_MOC_LITERAL(10, 106, 14), // "docAttachments"
QT_MOC_LITERAL(11, 121, 9), // "updateRev"
QT_MOC_LITERAL(12, 131, 4), // "load"
QT_MOC_LITERAL(13, 136, 4), // "save"
QT_MOC_LITERAL(14, 141, 9), // "deleteDoc"
QT_MOC_LITERAL(15, 151, 13), // "addAttachment"
QT_MOC_LITERAL(16, 165, 14), // "attachmentName"
QT_MOC_LITERAL(17, 180, 7), // "content"
QT_MOC_LITERAL(18, 188, 11), // "contentType"
QT_MOC_LITERAL(19, 200, 6), // "setDoc"
QT_MOC_LITERAL(20, 207, 4), // "json"
QT_MOC_LITERAL(21, 212, 6), // "getDoc"
QT_MOC_LITERAL(22, 219, 3), // "doc"
QT_MOC_LITERAL(23, 223, 16), // "QQmlPropertyMap*"
QT_MOC_LITERAL(24, 240, 5), // "docId"
QT_MOC_LITERAL(25, 246, 6) // "docRev"

    },
    "CouchDBDocument\0databaseChanged\0\0"
    "CouchDBDatabase*\0database\0idChanged\0"
    "id\0revChanged\0rev\0attachmentsChanged\0"
    "docAttachments\0updateRev\0load\0save\0"
    "deleteDoc\0addAttachment\0attachmentName\0"
    "content\0contentType\0setDoc\0json\0getDoc\0"
    "doc\0QQmlPropertyMap*\0docId\0docRev"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CouchDBDocument[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       5,   96, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       7,    1,   75,    2, 0x06 /* Public */,
       9,    1,   78,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    0,   81,    2, 0x02 /* Public */,
      12,    0,   82,    2, 0x02 /* Public */,
      13,    0,   83,    2, 0x02 /* Public */,
      14,    0,   84,    2, 0x02 /* Public */,
      15,    3,   85,    2, 0x02 /* Public */,
      19,    1,   92,    2, 0x02 /* Public */,
      21,    0,   95,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QJsonObject,   10,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QString,   16,   17,   18,
    QMetaType::Void, QMetaType::QJsonObject,   20,
    QMetaType::QJsonObject,

 // properties: name, type, flags
       4, 0x80000000 | 3, 0x0049510b,
      22, 0x80000000 | 23, 0x00095409,
      24, QMetaType::QString, 0x00495003,
      25, QMetaType::QString, 0x00495003,
      10, QMetaType::QJsonObject, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       1,
       2,
       3,

       0        // eod
};

void CouchDBDocument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CouchDBDocument *_t = static_cast<CouchDBDocument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->databaseChanged((*reinterpret_cast< CouchDBDatabase*(*)>(_a[1]))); break;
        case 1: _t->idChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->revChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->attachmentsChanged((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->updateRev(); break;
        case 5: _t->load(); break;
        case 6: _t->save(); break;
        case 7: _t->deleteDoc(); break;
        case 8: _t->addAttachment((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 9: _t->setDoc((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 10: { QJsonObject _r = _t->getDoc();
            if (_a[0]) *reinterpret_cast< QJsonObject*>(_a[0]) = std::move(_r); }  break;
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
            typedef void (CouchDBDocument::*_t)(CouchDBDatabase * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDocument::databaseChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CouchDBDocument::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDocument::idChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CouchDBDocument::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDocument::revChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CouchDBDocument::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CouchDBDocument::attachmentsChanged)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CouchDBDatabase* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQmlPropertyMap* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        CouchDBDocument *_t = static_cast<CouchDBDocument *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< CouchDBDatabase**>(_v) = _t->database(); break;
        case 1: *reinterpret_cast< QQmlPropertyMap**>(_v) = _t->doc(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->rev(); break;
        case 4: *reinterpret_cast< QJsonObject*>(_v) = _t->attachments(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        CouchDBDocument *_t = static_cast<CouchDBDocument *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDatabase(*reinterpret_cast< CouchDBDatabase**>(_v)); break;
        case 2: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setRev(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CouchDBDocument::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CouchDBDocument.data,
      qt_meta_data_CouchDBDocument,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CouchDBDocument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CouchDBDocument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CouchDBDocument.stringdata0))
        return static_cast<void*>(const_cast< CouchDBDocument*>(this));
    return QObject::qt_metacast(_clname);
}

int CouchDBDocument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
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
void CouchDBDocument::databaseChanged(CouchDBDatabase * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CouchDBDocument::idChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CouchDBDocument::revChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CouchDBDocument::attachmentsChanged(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
