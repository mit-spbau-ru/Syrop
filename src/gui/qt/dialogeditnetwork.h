#ifndef DIALOGEDITNETWORK_H
#define DIALOGEDITNETWORK_H

#include <QDialog>
#include "inidata.h"

namespace Ui {
class DialogEditNetwork;
}

class DialogEditNetwork : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogEditNetwork(QWidget *parent, const QString& networkName);
    ~DialogEditNetwork();
    
private:
    Ui::DialogEditNetwork *ui;
    const QString& networkName;
    bool isEdited;
    utils::attributes attrs;

private slots:
    bool checkText();
    void onChanged();
    void onSave();    
    
};

#endif // DIALOGEDITNETWORK_H
