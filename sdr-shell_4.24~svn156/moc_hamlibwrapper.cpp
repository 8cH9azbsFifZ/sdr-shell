/****************************************************************************
** Meta object code from reading C++ file 'hamlibwrapper.h'
**
** Created: Sun Sep 4 21:23:28 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "hamlibwrapper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hamlibwrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_hamlibWrapper[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      31,   14,   14,   14, 0x05,
      50,   48,   14,   14, 0x05,
      79,   14,   14,   14, 0x05,
     105,   14,   14,   14, 0x05,
     132,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     146,   48,   14,   14, 0x0a,
     173,   14,   14,   14, 0x0a,
     195,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_hamlibWrapper[] = {
    "hamlibWrapper\0\0newFreq(double)\0"
    "nowTransmit(int)\0,\0rigChangedMode(rmode_t,bool)\0"
    "slopeLowChangedByRig(int)\0"
    "slopeHighChangedByRig(int)\0rigPitch(int)\0"
    "setMode(rmode_t,pbwidth_t)\0"
    "pollSlopeTuning(bool)\0useMuteXmit(bool)\0"
};

const QMetaObject hamlibWrapper::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_hamlibWrapper,
      qt_meta_data_hamlibWrapper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &hamlibWrapper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *hamlibWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *hamlibWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hamlibWrapper))
        return static_cast<void*>(const_cast< hamlibWrapper*>(this));
    return QThread::qt_metacast(_clname);
}

int hamlibWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFreq((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: nowTransmit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: rigChangedMode((*reinterpret_cast< rmode_t(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: slopeLowChangedByRig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: slopeHighChangedByRig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: rigPitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setMode((*reinterpret_cast< rmode_t(*)>(_a[1])),(*reinterpret_cast< pbwidth_t(*)>(_a[2]))); break;
        case 7: pollSlopeTuning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: useMuteXmit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void hamlibWrapper::newFreq(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void hamlibWrapper::nowTransmit(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void hamlibWrapper::rigChangedMode(rmode_t _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void hamlibWrapper::slopeLowChangedByRig(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void hamlibWrapper::slopeHighChangedByRig(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void hamlibWrapper::rigPitch(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
