/****************************************************************************
** Meta object code from reading C++ file 'memorycell.h'
**
** Created: Wed Aug 31 00:30:56 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "memorycell.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'memorycell.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MemoryCell[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      30,   11,   11,   11, 0x05,
      49,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MemoryCell[] = {
    "MemoryCell\0\0read(MemoryCell*)\0"
    "write(MemoryCell*)\0display(MemoryCell*)\0"
};

const QMetaObject MemoryCell::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_MemoryCell,
      qt_meta_data_MemoryCell, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MemoryCell::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MemoryCell::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MemoryCell::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MemoryCell))
        return static_cast<void*>(const_cast< MemoryCell*>(this));
    return QLabel::qt_metacast(_clname);
}

int MemoryCell::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: read((*reinterpret_cast< MemoryCell*(*)>(_a[1]))); break;
        case 1: write((*reinterpret_cast< MemoryCell*(*)>(_a[1]))); break;
        case 2: display((*reinterpret_cast< MemoryCell*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MemoryCell::read(MemoryCell * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MemoryCell::write(MemoryCell * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MemoryCell::display(MemoryCell * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE