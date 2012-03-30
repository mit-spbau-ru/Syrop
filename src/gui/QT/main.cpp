#include <QtGui>

#include "mainwindow.h"
#include "datamodel.h"

using namespace utils;
using namespace std;

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    
    MainWindow mainWindow;
    mainWindow.show();
    
    DataModel::getInstance(&mainWindow);
    DataModel::getInstance();
    
    return a.exec();
}
