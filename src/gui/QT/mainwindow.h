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
public slots:
    void onCurrentNetwokEdited();
private slots:
    // data model
    void onLoad();
    void onAddNetwork(QString const & title);
    void onRemoveNetwok(QString const & title);
    void onUpdateNetwork(QString const & title);
    void onAddApplication(QString const & title);
    void onRemoveApplication(QString const & title);
    // front end
    void addNetwork();
    void updateCurrentNetwork();
    void removeCurrentNetwork();
    void changeCurrentNetwork(QString const &);
    void addApplication();
    void removeApplication();
    void showAbout();
private:
    /**
     * Fill network list from DatamModel
     * and bind signals from list to tabs
     */
    QString currentNetworkName;
    void bindData();
    Ui::MainWindow *ui;
    bool isCurrentNetworkEdited;
};

#endif // MAINWINDOW_H
