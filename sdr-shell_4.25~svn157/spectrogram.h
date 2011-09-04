#ifndef SDXCVR_SPECTROGRAM_H
#define SDXCVR_SPECTROGRAM_H

#include <qwidget.h>

class Spectrogram : public QWidget
{
    Q_OBJECT
    
    public:
        Spectrogram(QWidget *parent = 0, const char *name = 0);

    private:
        int mouseMoving;

    protected:
        void mouseReleaseEvent( QMouseEvent * );
        void mouseMoveEvent( QMouseEvent * );

    signals:
        void tune1( int );
        void tune2( int );
        void plot( int );
	void movement( int );
};
#endif
