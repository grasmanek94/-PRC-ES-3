/****************************************************************************
** Meta object code from reading C++ file 'sychronouswebsocketsresponder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QT/sychronouswebsocketsresponder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sychronouswebsocketsresponder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SychronousWebSocketsResponder_t {
    QByteArrayData data[4];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SychronousWebSocketsResponder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SychronousWebSocketsResponder_t qt_meta_stringdata_SychronousWebSocketsResponder = {
    {
QT_MOC_LITERAL(0, 0, 29), // "SychronousWebSocketsResponder"
QT_MOC_LITERAL(1, 30, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 7) // "message"

    },
    "SychronousWebSocketsResponder\0"
    "onTextMessageReceived\0\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SychronousWebSocketsResponder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void SychronousWebSocketsResponder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SychronousWebSocketsResponder *_t = static_cast<SychronousWebSocketsResponder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SychronousWebSocketsResponder::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SychronousWebSocketsResponder.data,
      qt_meta_data_SychronousWebSocketsResponder,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SychronousWebSocketsResponder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SychronousWebSocketsResponder::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SychronousWebSocketsResponder.stringdata0))
        return static_cast<void*>(const_cast< SychronousWebSocketsResponder*>(this));
    return QThread::qt_metacast(_clname);
}

int SychronousWebSocketsResponder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
