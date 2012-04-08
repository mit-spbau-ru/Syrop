#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "proxysettings.h"
//#include "appsettings.h"

namespace Ui { class MainWindow; }

/**
 * MainWindow 
 * - contains DataModel and remove it by itself. (QT parent)
 * - manages other windows
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    // data model
    void onLoad();
    void onAddNetwork(QString const & title);
    // front end
    void addNetwork();
    void changeCurrentNetwork(int);
    void showAbout();    
private:
    void bindData();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
