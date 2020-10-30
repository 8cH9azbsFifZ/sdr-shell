#ifndef SDXCVR_SPECTRUM_H
#define SDXCVR_SPECTRUM_H

#include <qwidget.h>

class Spectrum : public QWidget
{
    Q_OBJECT
    
    public:
        Spectrum(QWidget *parent = 0, const char *name = 0, WFlags f = 0 );

    private:
        int mouseMoving;

    protected:
        void mouseReleaseEvent( QMouseEvent * );
        void mouseMoveEvent( QMouseEvent * );

    signals:
		void movement( int );
		void tune( int );
};
#endif
