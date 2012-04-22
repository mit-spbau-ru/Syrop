#ifndef DIALOGADDAPP_H
#define DIALOGADDAPP_H

#include <QDialog>
#include "proxysettings.h"

namespace Ui {
class DialogAddApp;
}

class DialogAddApp : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddApp(QWidget *parent, utils::ProxySettings & apps);
    ~DialogAddApp();
    
private:
    utils::ProxySettings & proxySettings;
    Ui::DialogAddApp *ui;
};

#endif // DIALOGADDAPP_H
