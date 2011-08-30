/****************************************************************************
** Meta object code from reading C++ file 'spectrogram.h'
**
** Created: Wed Aug 31 01:05:30 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "spectrogram.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spectrogram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Spectrogram[] = {

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
      13,   12,   12,   12, 0x05,
      24,   12,   12,   12, 0x05,
      35,   12,   12,   12, 0x05,
      46,   12,   12,   12, 0x05,
      56,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Spectrogram[] = {
    "Spectrogram\0\0tune1(int)\0tune2(int)\0"
    "tune3(int)\0plot(int)\0movement(int)\0"
};

const QMetaObject Spectrogram::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Spectrogram,
      qt_meta_data_Spectrogram, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Spectrogram::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Spectrogram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Spectrogram::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Spectrogram))
        return static_cast<void*>(const_cast< Spectrogram*>(this));
    return QWidget::qt_metacast(_clname);
}

int Spectrogram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tune1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: tune2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: tune3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: plot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: movement((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Spectrogram::tune1(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Spectrogram::tune2(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Spectrogram::tune3(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Spectrogram::plot(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Spectrogram::movement(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
