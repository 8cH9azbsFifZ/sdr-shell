#include "pbscale.h"

PassBandScale::PassBandScale(QWidget *parent, const char *name, WFlags f ) 
	: QWidget(parent, name, f)
{
	setMouseTracking( true );
}

void PassBandScale::mouseMoveEvent( QMouseEvent *e )
{
        emit movement( e->x() );
}

void PassBandScale::mousePressEvent( QMouseEvent *e )
{
	x0 = e->x();

	if ( e->button() == LeftButton )
		emit set_lower_pb( x0 );
	if ( e->button() == RightButton )	
		emit set_upper_pb( x0 );
}
