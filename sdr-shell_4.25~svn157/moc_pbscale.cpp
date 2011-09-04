/****************************************************************************
** PassBandScale meta object code from reading C++ file 'pbscale.h'
**
** Created: Mon Sep 5 00:21:25 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "pbscale.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PassBandScale::className() const
{
    return "PassBandScale";
}

QMetaObject *PassBandScale::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PassBandScale( "PassBandScale", &PassBandScale::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PassBandScale::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PassBandScale", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PassBandScale::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PassBandScale", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PassBandScale::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"set_lower_pb", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"set_upper_pb", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"movement", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "set_lower_pb(int)", &signal_0, QMetaData::Protected },
	{ "set_upper_pb(int)", &signal_1, QMetaData::Protected },
	{ "movement(int)", &signal_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"PassBandScale", parentObject,
	0, 0,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PassBandScale.setMetaObject( metaObj );
    return metaObj;
}

void* PassBandScale::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PassBandScale" ) )
	return this;
    return QWidget::qt_cast( clname );
}

// SIGNAL set_lower_pb
void PassBandScale::set_lower_pb( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

// SIGNAL set_upper_pb
void PassBandScale::set_upper_pb( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 1, t0 );
}

// SIGNAL movement
void PassBandScale::movement( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

bool PassBandScale::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool PassBandScale::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: set_lower_pb((int)static_QUType_int.get(_o+1)); break;
    case 1: set_upper_pb((int)static_QUType_int.get(_o+1)); break;
    case 2: movement((int)static_QUType_int.get(_o+1)); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool PassBandScale::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool PassBandScale::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
