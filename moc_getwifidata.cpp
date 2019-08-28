/****************************************************************************
** Meta object code from reading C++ file 'getwifidata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "getwifidata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getwifidata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_getWifiData_t {
    QByteArrayData data[6];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_getWifiData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_getWifiData_t qt_meta_stringdata_getWifiData = {
    {
QT_MOC_LITERAL(0, 0, 11), // "getWifiData"
QT_MOC_LITERAL(1, 12, 6), // "change"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "display"
QT_MOC_LITERAL(4, 28, 8), // "doChange"
QT_MOC_LITERAL(5, 37, 9) // "dodisplay"

    },
    "getWifiData\0change\0\0display\0doChange\0"
    "dodisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_getWifiData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void getWifiData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        getWifiData *_t = static_cast<getWifiData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change(); break;
        case 1: _t->display(); break;
        case 2: _t->doChange(); break;
        case 3: _t->dodisplay(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (getWifiData::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&getWifiData::change)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (getWifiData::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&getWifiData::display)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject getWifiData::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_getWifiData.data,
      qt_meta_data_getWifiData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *getWifiData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *getWifiData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_getWifiData.stringdata0))
        return static_cast<void*>(const_cast< getWifiData*>(this));
    return QThread::qt_metacast(_clname);
}

int getWifiData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void getWifiData::change()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void getWifiData::display()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
