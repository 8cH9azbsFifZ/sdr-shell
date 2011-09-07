/****************************************************************************
** Main_Widget meta object code from reading C++ file 'main_widget.h'
**
** Created: Wed Sep 7 19:28:52 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "main_widget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Main_Widget::className() const
{
    return "Main_Widget";
}

QMetaObject *Main_Widget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Main_Widget( "Main_Widget", &Main_Widget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Main_Widget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Main_Widget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Main_Widget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Main_Widget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Main_Widget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"finish", 0, 0 };
    static const QUMethod slot_1 = {"readMeter", 0, 0 };
    static const QUMethod slot_2 = {"readSpectrum", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"spectrogramClicked", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"plotSpectrum", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"tune", 1, param_slot_5 };
    static const QUMethod slot_6 = {"processorLoad", 0, 0 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"setTuneStep", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"toggle_NR", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"toggle_ANF", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"toggle_NB", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"toggle_BIN", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"toggle_MUTE", 1, param_slot_12 };
    static const QUParameter param_slot_13[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_13 = {"toggle_SPEC", 1, param_slot_13 };
    static const QUParameter param_slot_14[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"setFilter_l", 1, param_slot_14 };
    static const QUParameter param_slot_15[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_15 = {"setFilter_h", 1, param_slot_15 };
    static const QUParameter param_slot_16[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"setMode", 1, param_slot_16 };
    static const QUMethod slot_17 = {"setFilter", 0, 0 };
    static const QUParameter param_slot_18[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_18 = {"f_at_mousepointer", 1, param_slot_18 };
    static const QUParameter param_slot_19[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_19 = {"setLowerFilterScale", 1, param_slot_19 };
    static const QUParameter param_slot_20[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_20 = {"setUpperFilterScale", 1, param_slot_20 };
    static const QUParameter param_slot_21[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_21 = {"setCfg", 1, param_slot_21 };
    static const QUParameter param_slot_22[] = {
	{ 0, &static_QUType_ptr, "MemoryCell", QUParameter::In }
    };
    static const QUMethod slot_22 = {"readMem", 1, param_slot_22 };
    static const QUParameter param_slot_23[] = {
	{ 0, &static_QUType_ptr, "MemoryCell", QUParameter::In }
    };
    static const QUMethod slot_23 = {"writeMem", 1, param_slot_23 };
    static const QUParameter param_slot_24[] = {
	{ 0, &static_QUType_ptr, "MemoryCell", QUParameter::In }
    };
    static const QUMethod slot_24 = {"displayMem", 1, param_slot_24 };
    static const QUParameter param_slot_25[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_25 = {"displayNCO", 1, param_slot_25 };
    static const QUMethod slot_26 = {"updateCallsign", 0, 0 };
    static const QUMethod slot_27 = {"updateLOFreq", 0, 0 };
    static const QUParameter param_slot_28[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_28 = {"updateIQGain", 1, param_slot_28 };
    static const QUParameter param_slot_29[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_29 = {"updateIQPhase", 1, param_slot_29 };
    static const QUParameter param_slot_30[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_30 = {"setPolyFFT", 1, param_slot_30 };
    static const QUParameter param_slot_31[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_31 = {"setFFTWindow", 1, param_slot_31 };
    static const QUParameter param_slot_32[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_32 = {"setSpectrumType", 1, param_slot_32 };
    static const QUParameter param_slot_33[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_33 = {"setAGC", 1, param_slot_33 };
    static const QUParameter param_slot_34[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_34 = {"calibrateSpec", 1, param_slot_34 };
    static const QUParameter param_slot_35[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_35 = {"calibrateMetr", 1, param_slot_35 };
    static const QMetaData slot_tbl[] = {
	{ "finish()", &slot_0, QMetaData::Public },
	{ "readMeter()", &slot_1, QMetaData::Public },
	{ "readSpectrum()", &slot_2, QMetaData::Public },
	{ "spectrogramClicked(int)", &slot_3, QMetaData::Public },
	{ "plotSpectrum(int)", &slot_4, QMetaData::Public },
	{ "tune(int)", &slot_5, QMetaData::Public },
	{ "processorLoad()", &slot_6, QMetaData::Public },
	{ "setTuneStep(int)", &slot_7, QMetaData::Public },
	{ "toggle_NR(int)", &slot_8, QMetaData::Public },
	{ "toggle_ANF(int)", &slot_9, QMetaData::Public },
	{ "toggle_NB(int)", &slot_10, QMetaData::Public },
	{ "toggle_BIN(int)", &slot_11, QMetaData::Public },
	{ "toggle_MUTE(int)", &slot_12, QMetaData::Public },
	{ "toggle_SPEC(int)", &slot_13, QMetaData::Public },
	{ "setFilter_l(int)", &slot_14, QMetaData::Public },
	{ "setFilter_h(int)", &slot_15, QMetaData::Public },
	{ "setMode(int)", &slot_16, QMetaData::Public },
	{ "setFilter()", &slot_17, QMetaData::Public },
	{ "f_at_mousepointer(int)", &slot_18, QMetaData::Public },
	{ "setLowerFilterScale(int)", &slot_19, QMetaData::Public },
	{ "setUpperFilterScale(int)", &slot_20, QMetaData::Public },
	{ "setCfg(int)", &slot_21, QMetaData::Public },
	{ "readMem(MemoryCell*)", &slot_22, QMetaData::Public },
	{ "writeMem(MemoryCell*)", &slot_23, QMetaData::Public },
	{ "displayMem(MemoryCell*)", &slot_24, QMetaData::Public },
	{ "displayNCO(int)", &slot_25, QMetaData::Public },
	{ "updateCallsign()", &slot_26, QMetaData::Public },
	{ "updateLOFreq()", &slot_27, QMetaData::Public },
	{ "updateIQGain(int)", &slot_28, QMetaData::Public },
	{ "updateIQPhase(int)", &slot_29, QMetaData::Public },
	{ "setPolyFFT(int)", &slot_30, QMetaData::Public },
	{ "setFFTWindow(int)", &slot_31, QMetaData::Public },
	{ "setSpectrumType(int)", &slot_32, QMetaData::Public },
	{ "setAGC(int)", &slot_33, QMetaData::Public },
	{ "calibrateSpec(int)", &slot_34, QMetaData::Public },
	{ "calibrateMetr(int)", &slot_35, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Main_Widget", parentObject,
	slot_tbl, 36,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Main_Widget.setMetaObject( metaObj );
    return metaObj;
}

void* Main_Widget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Main_Widget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool Main_Widget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: finish(); break;
    case 1: readMeter(); break;
    case 2: readSpectrum(); break;
    case 3: spectrogramClicked((int)static_QUType_int.get(_o+1)); break;
    case 4: plotSpectrum((int)static_QUType_int.get(_o+1)); break;
    case 5: tune((int)static_QUType_int.get(_o+1)); break;
    case 6: processorLoad(); break;
    case 7: setTuneStep((int)static_QUType_int.get(_o+1)); break;
    case 8: toggle_NR((int)static_QUType_int.get(_o+1)); break;
    case 9: toggle_ANF((int)static_QUType_int.get(_o+1)); break;
    case 10: toggle_NB((int)static_QUType_int.get(_o+1)); break;
    case 11: toggle_BIN((int)static_QUType_int.get(_o+1)); break;
    case 12: toggle_MUTE((int)static_QUType_int.get(_o+1)); break;
    case 13: toggle_SPEC((int)static_QUType_int.get(_o+1)); break;
    case 14: setFilter_l((int)static_QUType_int.get(_o+1)); break;
    case 15: setFilter_h((int)static_QUType_int.get(_o+1)); break;
    case 16: setMode((int)static_QUType_int.get(_o+1)); break;
    case 17: setFilter(); break;
    case 18: f_at_mousepointer((int)static_QUType_int.get(_o+1)); break;
    case 19: setLowerFilterScale((int)static_QUType_int.get(_o+1)); break;
    case 20: setUpperFilterScale((int)static_QUType_int.get(_o+1)); break;
    case 21: setCfg((int)static_QUType_int.get(_o+1)); break;
    case 22: readMem((MemoryCell*)static_QUType_ptr.get(_o+1)); break;
    case 23: writeMem((MemoryCell*)static_QUType_ptr.get(_o+1)); break;
    case 24: displayMem((MemoryCell*)static_QUType_ptr.get(_o+1)); break;
    case 25: displayNCO((int)static_QUType_int.get(_o+1)); break;
    case 26: updateCallsign(); break;
    case 27: updateLOFreq(); break;
    case 28: updateIQGain((int)static_QUType_int.get(_o+1)); break;
    case 29: updateIQPhase((int)static_QUType_int.get(_o+1)); break;
    case 30: setPolyFFT((int)static_QUType_int.get(_o+1)); break;
    case 31: setFFTWindow((int)static_QUType_int.get(_o+1)); break;
    case 32: setSpectrumType((int)static_QUType_int.get(_o+1)); break;
    case 33: setAGC((int)static_QUType_int.get(_o+1)); break;
    case 34: calibrateSpec((int)static_QUType_int.get(_o+1)); break;
    case 35: calibrateMetr((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Main_Widget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Main_Widget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool Main_Widget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
