/****************************************************************************
** Meta object code from reading C++ file 'main_widget.h'
**
** Created: Wed Sep 7 19:15:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Main_Widget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      22,   12,   12,   12, 0x0a,
      34,   12,   12,   12, 0x0a,
      49,   12,   12,   12, 0x0a,
      73,   12,   12,   12, 0x0a,
      91,   12,   12,   12, 0x0a,
     101,   12,   12,   12, 0x0a,
     117,   12,   12,   12, 0x0a,
     134,   12,   12,   12, 0x0a,
     149,   12,   12,   12, 0x0a,
     165,   12,   12,   12, 0x0a,
     180,   12,   12,   12, 0x0a,
     196,   12,   12,   12, 0x0a,
     213,   12,   12,   12, 0x0a,
     230,   12,   12,   12, 0x0a,
     247,   12,   12,   12, 0x0a,
     264,   12,   12,   12, 0x0a,
     277,   12,   12,   12, 0x0a,
     289,   12,   12,   12, 0x0a,
     312,   12,   12,   12, 0x0a,
     337,   12,   12,   12, 0x0a,
     362,   12,   12,   12, 0x0a,
     374,   12,   12,   12, 0x0a,
     395,   12,   12,   12, 0x0a,
     417,   12,   12,   12, 0x0a,
     441,   12,   12,   12, 0x0a,
     457,   12,   12,   12, 0x0a,
     474,   12,   12,   12, 0x0a,
     489,   12,   12,   12, 0x0a,
     507,   12,   12,   12, 0x0a,
     526,   12,   12,   12, 0x0a,
     542,   12,   12,   12, 0x0a,
     560,   12,   12,   12, 0x0a,
     581,   12,   12,   12, 0x0a,
     593,   12,   12,   12, 0x0a,
     612,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Main_Widget[] = {
    "Main_Widget\0\0finish()\0readMeter()\0"
    "readSpectrum()\0spectrogramClicked(int)\0"
    "plotSpectrum(int)\0tune(int)\0processorLoad()\0"
    "setTuneStep(int)\0toggle_NR(int)\0"
    "toggle_ANF(int)\0toggle_NB(int)\0"
    "toggle_BIN(int)\0toggle_MUTE(int)\0"
    "toggle_SPEC(int)\0setFilter_l(int)\0"
    "setFilter_h(int)\0setMode(int)\0setFilter()\0"
    "f_at_mousepointer(int)\0setLowerFilterScale(int)\0"
    "setUpperFilterScale(int)\0setCfg(int)\0"
    "readMem(MemoryCell*)\0writeMem(MemoryCell*)\0"
    "displayMem(MemoryCell*)\0displayNCO(int)\0"
    "updateCallsign()\0updateLOFreq()\0"
    "updateIQGain(int)\0updateIQPhase(int)\0"
    "setPolyFFT(int)\0setFFTWindow(int)\0"
    "setSpectrumType(int)\0setAGC(int)\0"
    "calibrateSpec(int)\0calibrateMetr(int)\0"
};

const QMetaObject Main_Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Main_Widget,
      qt_meta_data_Main_Widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Main_Widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Main_Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Main_Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Main_Widget))
        return static_cast<void*>(const_cast< Main_Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Main_Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finish(); break;
        case 1: readMeter(); break;
        case 2: readSpectrum(); break;
        case 3: spectrogramClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: plotSpectrum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: tune((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: processorLoad(); break;
        case 7: setTuneStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: toggle_NR((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: toggle_ANF((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: toggle_NB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: toggle_BIN((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: toggle_MUTE((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: toggle_SPEC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: setFilter_l((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setFilter_h((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: setMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: setFilter(); break;
        case 18: f_at_mousepointer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setLowerFilterScale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: setUpperFilterScale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: setCfg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: readMem((*reinterpret_cast< MemoryCell*(*)>(_a[1]))); break;
        case 23: writeMem((*reinterpret_cast< MemoryCell*(*)>(_a[1]))); break;
        case 24: displayMem((*reinterpret_cast< MemoryCell*(*)>(_a[1]))); break;
        case 25: displayNCO((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: updateCallsign(); break;
        case 27: updateLOFreq(); break;
        case 28: updateIQGain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: updateIQPhase((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: setPolyFFT((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: setFFTWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: setSpectrumType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: setAGC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: calibrateSpec((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: calibrateMetr((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
