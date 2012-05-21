#ifndef DIALOGEDITNETWORK_H
#define DIALOGEDITNETWORK_H

#include <QDialog>

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

private slots:
    void onChanged();
    void onSave();    
    
};

#endif // DIALOGEDITNETWORK_H
