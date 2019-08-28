/****************************************************************************
** Meta object code from reading C++ file 'sniff80211.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sniff80211.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sniff80211.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sniff80211_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sniff80211_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sniff80211_t qt_meta_stringdata_sniff80211 = {
    {
QT_MOC_LITERAL(0, 0, 10), // "sniff80211"
QT_MOC_LITERAL(1, 11, 11), // "datachanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9) // "macupdate"

    },
    "sniff80211\0datachanged\0\0macupdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sniff80211[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sniff80211::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sniff80211 *_t = static_cast<sniff80211 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->datachanged(); break;
        case 1: _t->macupdate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (sniff80211::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sniff80211::datachanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (sniff80211::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sniff80211::macupdate)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject sniff80211::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sniff80211.data,
      qt_meta_data_sniff80211,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *sniff80211::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sniff80211::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_sniff80211.stringdata0))
        return static_cast<void*>(const_cast< sniff80211*>(this));
    return QWidget::qt_metacast(_clname);
}

int sniff80211::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void sniff80211::datachanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void sniff80211::macupdate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
