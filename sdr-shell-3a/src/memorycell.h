#ifndef MEMORYCELL_H
#define MEMORYCELL_H

#include <qlabel.h>
#include <qstring.h>
#include <hamlib/rig.h>

class MemoryCell : public QLabel
{
    Q_OBJECT
    
    public:
        MemoryCell(QWidget *parent = 0, const char *name = 0);

        void setID( int );
        void setMemo( QString );
        void setFrequency( long long int );
        void setMode( rmode_t );
        void setFilter( int, int );
        
        int getID();
        int getMemo();
        long long int getFrequency();        
        int getMode();
        int getFilter_l();
        int getFilter_h(); 
        
    private:
        int id;
        QString memo;
        long long int frequency;
        int mode;
        int filter_l;
        int filter_h;

    protected:
        void mouseReleaseEvent ( QMouseEvent * );
        void enterEvent ( QEvent * );

    signals:
        void read( MemoryCell * );
        void write( MemoryCell * );
        void display( MemoryCell * );
};
#endif
