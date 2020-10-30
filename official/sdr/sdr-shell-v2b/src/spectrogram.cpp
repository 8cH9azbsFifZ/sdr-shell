#include "spectrogram.h"

Spectrogram::Spectrogram(QWidget *parent, const char *name) : QWidget(parent, name)
{
  //setMouseTracking( true );

    mouseMoving = 0;
}

void Spectrogram::mouseReleaseEvent( QMouseEvent *e )
{
    if ( !mouseMoving && e->state() == LeftButton )
        emit tune1( e->x() );

    if ( !mouseMoving && e->state() == RightButton )
        emit plot( e->y() );    

    mouseMoving = false;
}

void Spectrogram::mouseMoveEvent( QMouseEvent *e )
{
    static int x0 = 0;
    int output;

    mouseMoving = true;

    if ( x0 - e->x() >= 0 )
        output = 1;
    else
        output = -1;

    if ( e->state() == LeftButton ) 
        emit tune2( output );
    else if ( e->state() == RightButton )
        emit tune2( output * 10 );
    else if ( e->state() == MidButton )
        emit tune2( output * 100 );
    else
        emit movement( e->x() );

    x0 = e->x();
}
