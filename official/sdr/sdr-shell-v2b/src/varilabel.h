#ifndef VARILABEL_H
#define VARILABEL_H

#include <qlabel.h>

class Varilabel : public QLabel
{
    Q_OBJECT
    
    public:
        Varilabel(QWidget *parent = 0, const char *name = 0);
    void setLabel( int );

    private:
        int label;

    protected:
        void mouseMoveEvent ( QMouseEvent * );
        void mouseReleaseEvent ( QMouseEvent * );

    signals:
        void y( int );
        void pulse( int );
        void mouseRelease( int );

};
#endif
