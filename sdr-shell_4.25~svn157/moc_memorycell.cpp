/****************************************************************************
** MemoryCell meta object code from reading C++ file 'memorycell.h'
**
** Created: Mon Sep 5 00:21:24 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "memorycell.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MemoryCell::className() const
{
    return "MemoryCell";
}

QMetaObject *MemoryCell::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MemoryCell( "MemoryCell", &MemoryCell::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MemoryCell::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MemoryCell", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MemoryCell::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MemoryCell", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MemoryCell::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QLabel::staticMetaObject();
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_ptr, "MemoryCell", QUParameter::In }
    };
    static const QUMethod signal_0 = {"read", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_ptr, "MemoryCell", QUParameter::In }
    };
    static const QUMethod signal_1 = {"write", 1, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ 0, &static_QUType_ptr, "MemoryCell", QUParameter::In }
    };
    static const QUMethod signal_2 = {"display", 1, param_signal_2 };
    static const QMetaData signal_tbl[] = {
	{ "read(MemoryCell*)", &signal_0, QMetaData::Protected },
	{ "write(MemoryCell*)", &signal_1, QMetaData::Protected },
	{ "display(MemoryCell*)", &signal_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MemoryCell", parentObject,
	0, 0,
	signal_tbl, 3,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MemoryCell.setMetaObject( metaObj );
    return metaObj;
}

void* MemoryCell::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MemoryCell" ) )
	return this;
    return QLabel::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL read
void MemoryCell::read( MemoryCell* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL write
void MemoryCell::write( MemoryCell* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

// SIGNAL display
void MemoryCell::display( MemoryCell* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

bool MemoryCell::qt_invoke( int _id, QUObject* _o )
{
    return QLabel::qt_invoke(_id,_o);
}

bool MemoryCell::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: read((MemoryCell*)static_QUType_ptr.get(_o+1)); break;
    case 1: write((MemoryCell*)static_QUType_ptr.get(_o+1)); break;
    case 2: display((MemoryCell*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QLabel::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool MemoryCell::qt_property( int id, int f, QVariant* v)
{
    return QLabel::qt_property( id, f, v);
}

bool MemoryCell::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
