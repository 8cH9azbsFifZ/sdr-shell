/****************************************************************************
** Varilabel meta object code from reading C++ file 'varilabel.h'
**
** Created: Mon Sep 5 00:21:24 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "varilabel.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Varilabel::className() const
{
    return "Varilabel";
}

QMetaObject *Varilabel::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Varilabel( "Varilabel", &Varilabel::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Varilabel::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Varilabel", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Varilabel::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Varilabel", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Varilabel::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QLabel::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"y", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"pulse", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"mouseRelease", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "y(int)", &signal_0, QMetaData::Protected },
	{ "pulse(int)", &signal_1, QMetaData::Protected },
	{ "mouseRelease(int)", &signal_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"Varilabel", parentObject,
	0, 0,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Varilabel.setMetaObject( metaObj );
    return metaObj;
}

void* Varilabel::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Varilabel" ) )
	return this;
    return QLabel::qt_cast( clname );
}

// SIGNAL y
void Varilabel::y( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL pulse
void Varilabel::pulse( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

// SIGNAL mouseRelease
void Varilabel::mouseRelease( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

bool Varilabel::qt_invoke( int _id, QUObject* _o )
{
    return QLabel::qt_invoke(_id,_o);
}

bool Varilabel::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: y((int)static_QUType_int.get(_o+1)); break;
    case 1: pulse((int)static_QUType_int.get(_o+1)); break;
    case 2: mouseRelease((int)static_QUType_int.get(_o+1)); break;
    default:
	return QLabel::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool Varilabel::qt_property( int id, int f, QVariant* v)
{
    return QLabel::qt_property( id, f, v);
}

bool Varilabel::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
