#include "dialogaddapp.h"
#include "ui_dialogaddapp.h"
#include "datamodel.h"

DialogAddApp::DialogAddApp(QWidget *parent,  const QList<QString> & apps) 
    : QDialog(parent)
    , apps(apps)
    , ui(new Ui::DialogAddApp)
{
    
    ui->setupUi(this);
    
    QList<QString>::const_iterator it = apps.begin();
    QList<QString>::const_iterator end = apps.end();
    while(it != end) {
        ui->comboBox->addItem(*it);
        it++;
    }
    
}

DialogAddApp::~DialogAddApp()
{
    delete ui;
}
