#include "dialogaddapp.h"
#include "ui_dialogaddapp.h"
#include "datamodel.h"
#include "proxysettings.h"

using namespace utils;

DialogAddApp::DialogAddApp(QWidget *parent, utils::ProxySettings& proxySettings) 
    : QDialog(parent)
    , proxySettings(proxySettings)
    , ui(new Ui::DialogAddApp)
{
    
    ui->setupUi(this);
    
    
    QDataModel::proxyList::const_iterator it = DataModel::getInstance()->getApps().begin();
    QDataModel::proxyList::const_iterator end = DataModel::getInstance()->getApps().end();
    
  
    
    while(it != end) {
        if(!proxySettings.existsApp(it->first))
            ui->comboBox->addItem(QString(it->first.data()));
        it++;
    }
    
    
}

DialogAddApp::~DialogAddApp()
{
    delete ui;
}
