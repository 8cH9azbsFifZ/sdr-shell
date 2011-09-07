/****************************************************************************
** WorldMap meta object code from reading C++ file 'worldmap.h'
**
** Created: Wed Sep 7 19:28:54 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "worldmap.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *WorldMap::className() const
{
    return "WorldMap";
}

QMetaObject *WorldMap::metaObj = 0;
static QMetaObjectCleanUp cleanUp_WorldMap( "WorldMap", &WorldMap::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString WorldMap::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WorldMap", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString WorldMap::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "WorldMap", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* WorldMap::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QFrame::staticMetaObject();
    static const QUMethod slot_0 = {"compute", 0, 0 };
    static const QUMethod slot_1 = {"plot", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "compute()", &slot_0, QMetaData::Public },
	{ "plot()", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"WorldMap", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_WorldMap.setMetaObject( metaObj );
    return metaObj;
}

void* WorldMap::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "WorldMap" ) )
	return this;
    return QFrame::qt_cast( clname );
}

bool WorldMap::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: compute(); break;
    case 1: plot(); break;
    default:
	return QFrame::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool WorldMap::qt_emit( int _id, QUObject* _o )
{
    return QFrame::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool WorldMap::qt_property( int id, int f, QVariant* v)
{
    return QFrame::qt_property( id, f, v);
}

bool WorldMap::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
