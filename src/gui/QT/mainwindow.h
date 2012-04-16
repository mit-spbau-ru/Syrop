#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "proxysettings.h"

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
    void onRemoveNetwok(QString const & title);
    // front end
    void addNetwork();
    void removeCurrentNetwork();
    void changeCurrentNetwork(QString const &);
    void showAbout();
private:
    /**
     * Fill network list from DatamModel
     * and bind signals from list to tabs
     */
    void bindData();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
