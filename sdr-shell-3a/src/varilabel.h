#ifndef VARILABEL_H
#define VARILABEL_H

#include <qlabel.h>
#include <hamlib/rig.h>

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

class VariModelabel : public Varilabel
{
	Q_OBJECT
    
	public:
		VariModelabel(QWidget *parent = 0, const char *name = 0);
		void setLabel( rmode_t );
		
	private:
		rmode_t label;
		
	protected:
		void mouseReleaseEvent ( QMouseEvent *);
		
	signals:
		void mouseRelease( rmode_t, bool );

};
#endif
