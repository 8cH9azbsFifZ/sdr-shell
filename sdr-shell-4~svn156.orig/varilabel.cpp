#include "varilabel.h"

Varilabel::Varilabel(QWidget *parent, const char *name) : QLabel(parent, name)
{

}

void Varilabel::mouseMoveEvent( QMouseEvent *e )
{
    static int previous_y;
    
    // 1 pulse every 10 pixels
    if ( e->y() > previous_y + 10 || e->y() < previous_y - 10) {
        if ( e->y() > previous_y ) emit pulse( -1 );
        else emit pulse( 1 );
        previous_y = e->y();
    }

    // 1 pulse every pixel
    emit y( e->y() );
}

void Varilabel::mouseReleaseEvent ( QMouseEvent * )
{
    emit mouseRelease( label );
}

void Varilabel::setLabel( int l )
{
  label = l;
}
