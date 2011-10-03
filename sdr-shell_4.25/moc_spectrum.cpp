/****************************************************************************
** Spectrum meta object code from reading C++ file 'spectrum.h'
**
** Created: Wed Sep 7 19:28:55 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "spectrum.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Spectrum::className() const
{
    return "Spectrum";
}

QMetaObject *Spectrum::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Spectrum( "Spectrum", &Spectrum::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Spectrum::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Spectrum", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Spectrum::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Spectrum", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Spectrum::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"movement", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"tune", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "movement(int)", &signal_0, QMetaData::Protected },
	{ "tune(int)", &signal_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"Spectrum", parentObject,
	0, 0,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Spectrum.setMetaObject( metaObj );
    return metaObj;
}

void* Spectrum::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Spectrum" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL movement
void Spectrum::movement( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL tune
void Spectrum::tune( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

bool Spectrum::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool Spectrum::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: movement((int)static_QUType_int.get(_o+1)); break;
    case 1: tune((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Spectrum::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool Spectrum::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
