#include <QtGui>

#include "mainwindow.h"
#include "datamodel.h"

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return a.exec();
}
