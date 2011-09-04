/****************************************************************************
** Meta object code from reading C++ file 'varilabel.h'
**
** Created: Sun Sep 4 21:23:28 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "varilabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'varilabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Varilabel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      18,   10,   10,   10, 0x05,
      29,   10,   10,   10, 0x05,
      47,   10,   10,   10, 0x05,
      66,   10,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Varilabel[] = {
    "Varilabel\0\0y(int)\0pulse(int)\0"
    "mouseRelease(int)\0mouseRelease2(int)\0"
    "mouseRelease3(int)\0"
};

const QMetaObject Varilabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_Varilabel,
      qt_meta_data_Varilabel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Varilabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Varilabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Varilabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Varilabel))
        return static_cast<void*>(const_cast< Varilabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int Varilabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pulse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: mouseRelease((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: mouseRelease2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: mouseRelease3((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Varilabel::y(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Varilabel::pulse(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Varilabel::mouseRelease(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Varilabel::mouseRelease2(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Varilabel::mouseRelease3(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
static const uint qt_meta_data_VariModelabel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_VariModelabel[] = {
    "VariModelabel\0\0,,\0mouseRelease(rmode_t,bool,bool)\0"
};

const QMetaObject VariModelabel::staticMetaObject = {
    { &Varilabel::staticMetaObject, qt_meta_stringdata_VariModelabel,
      qt_meta_data_VariModelabel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VariModelabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VariModelabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VariModelabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VariModelabel))
        return static_cast<void*>(const_cast< VariModelabel*>(this));
    return Varilabel::qt_metacast(_clname);
}

int VariModelabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Varilabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mouseRelease((*reinterpret_cast< rmode_t(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void VariModelabel::mouseRelease(rmode_t _t1, bool _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
