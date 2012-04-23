#ifndef DIALOGADDAPP_H
#define DIALOGADDAPP_H

#include <QDialog>
#include "proxysettings.h"
#include "mainwindow.h"

namespace Ui {
class DialogAddApp;
}

class DialogAddApp : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddApp(MainWindow* mainWindow, utils::ProxySettings & apps);
    ~DialogAddApp();

private slots:
    void onChoose();
    
private:
    utils::ProxySettings& proxySettings;
    MainWindow* mainWindow;
    Ui::DialogAddApp* ui;
    
};

#endif // DIALOGADDAPP_H
