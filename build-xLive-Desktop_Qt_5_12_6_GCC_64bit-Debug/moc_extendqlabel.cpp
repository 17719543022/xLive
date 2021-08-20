/****************************************************************************
** Meta object code from reading C++ file 'extendqlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../xLive/extendqlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'extendqlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_extendQLabel_t {
    QByteArrayData data[12];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_extendQLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_extendQLabel_t qt_meta_stringdata_extendQLabel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "extendQLabel"
QT_MOC_LITERAL(1, 13, 12), // "uploadFailed"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "uploadSuccess"
QT_MOC_LITERAL(4, 41, 7), // "newPath"
QT_MOC_LITERAL(5, 49, 11), // "deleteFrame"
QT_MOC_LITERAL(6, 61, 7), // "on_Load"
QT_MOC_LITERAL(7, 69, 15), // "on_LoadResponse"
QT_MOC_LITERAL(8, 85, 14), // "QNetworkReply*"
QT_MOC_LITERAL(9, 100, 5), // "reply"
QT_MOC_LITERAL(10, 106, 20), // "on_hazardousResponse"
QT_MOC_LITERAL(11, 127, 11) // "actionsSlot"

    },
    "extendQLabel\0uploadFailed\0\0uploadSuccess\0"
    "newPath\0deleteFrame\0on_Load\0on_LoadResponse\0"
    "QNetworkReply*\0reply\0on_hazardousResponse\0"
    "actionsSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_extendQLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   54,    2, 0x08 /* Private */,
       7,    1,   55,    2, 0x08 /* Private */,
      10,    1,   58,    2, 0x08 /* Private */,
      11,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void extendQLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<extendQLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->uploadFailed(); break;
        case 1: _t->uploadSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->deleteFrame(); break;
        case 3: _t->on_Load(); break;
        case 4: _t->on_LoadResponse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->on_hazardousResponse((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->actionsSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (extendQLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&extendQLabel::uploadFailed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (extendQLabel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&extendQLabel::uploadSuccess)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (extendQLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&extendQLabel::deleteFrame)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject extendQLabel::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_extendQLabel.data,
    qt_meta_data_extendQLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *extendQLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *extendQLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_extendQLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int extendQLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void extendQLabel::uploadFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void extendQLabel::uploadSuccess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void extendQLabel::deleteFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
