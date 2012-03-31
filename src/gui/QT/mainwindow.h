#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "proxysettings.h"
#include "appsettings.h"

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
    void onLoad();
    void onAddApplicationSettings(utils::AppSettings const& title);
    void addNetwork();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
