/****************************************************************************
** Meta object code from reading C++ file 'lcdfreq.h'
**
** Created: Sun Aug 28 02:35:52 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lcdfreq.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lcdfreq.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LCDFreq[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      23,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_LCDFreq[] = {
    "LCDFreq\0\0tuneStep(int)\0tune3(int)\0"
};

const QMetaObject LCDFreq::staticMetaObject = {
    { &QLCDNumber::staticMetaObject, qt_meta_stringdata_LCDFreq,
      qt_meta_data_LCDFreq, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LCDFreq::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LCDFreq::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LCDFreq::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LCDFreq))
        return static_cast<void*>(const_cast< LCDFreq*>(this));
    return QLCDNumber::qt_metacast(_clname);
}

int LCDFreq::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tuneStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: tune3((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LCDFreq::tuneStep(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LCDFreq::tune3(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
