#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

/**
* MainWindow 
* - contains DataModel and remove it by itself. (QT parent)
* - manage other windows
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addNetwork();
    void onAddApplicationSettings(std::string const& title);
    
private:
    
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
