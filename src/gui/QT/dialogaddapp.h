#ifndef DIALOGADDAPP_H
#define DIALOGADDAPP_H

#include <QDialog>

namespace Ui {
class DialogAddApp;
}

class DialogAddApp : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddApp(QWidget *parent, QList<QString> const & apps);
    ~DialogAddApp();
    
private:
    QList<QString> const & apps;
    Ui::DialogAddApp *ui;
};

#endif // DIALOGADDAPP_H
