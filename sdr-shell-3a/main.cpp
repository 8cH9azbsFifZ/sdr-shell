#include <qapplication.h>
#include <qfontdatabase.h>
#include "main_widget.h"
#include "app.xpm"


int main (int argc, char **argv)
{
    QApplication app(argc, argv);
   
    Main_Widget *w = new Main_Widget( 0, "mainwidget");
    w->setIcon( app_xpm ); 
    app.setMainWidget( w );
    w->show();
    return app.exec();
}
