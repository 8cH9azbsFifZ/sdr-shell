#include "memorycell.h"

MemoryCell::MemoryCell(QWidget *parent, const char *name) : QLabel(parent, name)
{
    id = 0;
    frequency = 0;
    mode = 0;
    filter_l = -2400;
    filter_h = -20;

	setMouseTracking( true );
}

void MemoryCell::setID( int i )
{
    id = i;
}

void MemoryCell::setMode( int m )
{
    mode = m;
}

void MemoryCell::setFilter( int l, int h )
{
    filter_l = l;
    filter_h = h;
}

void MemoryCell::setFrequency( long long int f )
{
    frequency = f;
}

int MemoryCell::getID()
{
    return id;
}

int MemoryCell::getMode()
{
    return mode;
}

int MemoryCell::getFilter_l()
{
    return filter_l;
}

int MemoryCell::getFilter_h()
{
    return filter_h;
}

long long int MemoryCell::getFrequency()
{
    return frequency;
}

void MemoryCell::mouseReleaseEvent ( QMouseEvent *e )
{
    if ( e->state() == LeftButton )
        emit read( this );
    else if ( e->state() == MidButton )
        emit write( this );
}

void MemoryCell::enterEvent( QEvent * )
{
	emit display( this );
}
