/****************************************************************************
** Spectrogram meta object code from reading C++ file 'spectrogram.h'
**
** Created: Wed Sep 7 19:28:53 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "spectrogram.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Spectrogram::className() const
{
    return "Spectrogram";
}

QMetaObject *Spectrogram::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Spectrogram( "Spectrogram", &Spectrogram::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Spectrogram::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Spectrogram", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Spectrogram::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Spectrogram", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Spectrogram::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"tune1", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"tune2", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"plot", 1, param_signal_2 };
    static const QUParameter param_signal_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_3 = {"movement", 1, param_signal_3 };
    static const QMetaData signal_tbl[] = {
	{ "tune1(int)", &signal_0, QMetaData::Protected },
	{ "tune2(int)", &signal_1, QMetaData::Protected },
	{ "plot(int)", &signal_2, QMetaData::Protected },
	{ "movement(int)", &signal_3, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"Spectrogram", parentObject,
	0, 0,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Spectrogram.setMetaObject( metaObj );
    return metaObj;
}

void* Spectrogram::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Spectrogram" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL tune1
void Spectrogram::tune1( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL tune2
void Spectrogram::tune2( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

// SIGNAL plot
void Spectrogram::plot( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

// SIGNAL movement
void Spectrogram::movement( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 3, t0 );
}

bool Spectrogram::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool Spectrogram::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: tune1((int)static_QUType_int.get(_o+1)); break;
    case 1: tune2((int)static_QUType_int.get(_o+1)); break;
    case 2: plot((int)static_QUType_int.get(_o+1)); break;
    case 3: movement((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Spectrogram::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool Spectrogram::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
