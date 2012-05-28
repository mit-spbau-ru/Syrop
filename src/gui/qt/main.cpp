#include <QtGui>

#include "mainwindow.h"
#include "exception"
#include "iostream"

int main(int argc, char *argv[]) 
{   
    try{
        QApplication a(argc, argv);
        MainWindow mainWindow;
        mainWindow.show();
        return a.exec();
    } catch (std::exception const & e) {
        std::cout << e.what();
        return 1;
    } catch (...){
        std::cout << "unknown error occured";
        return 2;
    }
    
}
