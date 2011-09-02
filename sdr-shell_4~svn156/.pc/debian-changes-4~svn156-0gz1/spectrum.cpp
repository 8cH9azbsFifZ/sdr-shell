#include "spectrum.h"

Spectrum::Spectrum( QWidget *parent, const char *name, WFlags f ) 
	: QWidget( parent, name, f )
{
	setMouseTracking( true );
    mouseMoving = 0;
}

void Spectrum::mouseReleaseEvent( QMouseEvent *e )
{
	emit tune( e->x() );
}

void Spectrum::mouseMoveEvent( QMouseEvent *e )
{
	emit movement( e->x() );
}
