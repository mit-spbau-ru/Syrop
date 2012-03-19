#ifndef DIALOGADDNETWORK_H
#define DIALOGADDNETWORK_H

#include <QDialog>

namespace Ui {
class DialogAddNetwork;
}

class DialogAddNetwork : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAddNetwork(QWidget *parent = 0);
    ~DialogAddNetwork();
    
    QString const& getTitle() const;
    
private:
    Ui::DialogAddNetwork *ui;
};

#endif // DIALOGADDNETWORK_H
