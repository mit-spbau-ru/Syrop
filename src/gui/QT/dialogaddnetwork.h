#ifndef DIALOGADDNETWORK_H
#define DIALOGADDNETWORK_H

#include <QDialog>

#include "datamodel.h"

namespace Ui { class DialogAddNetwork; }

/**
 * Dialog for addition appliction settings
 */
class DialogAddNetwork : public QDialog
{
    Q_OBJECT
public:
    explicit DialogAddNetwork(QWidget *parent = 0);
    ~DialogAddNetwork();
private slots:
    void onSubmitChanges();
private:
    Ui::DialogAddNetwork *ui;
};

#endif // DIALOGADDNETWORK_H
