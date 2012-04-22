#include "dialogaddapp.h"
#include "ui_dialogaddapp.h"
#include "datamodel.h"
#include "proxysettings.h"

using namespace utils;

DialogAddApp::DialogAddApp(MainWindow* mainWindow, utils::ProxySettings& proxySettings) 
    : QDialog(mainWindow)
    , mainWindow(mainWindow)
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
    
    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(onChoose()));
    
}

void DialogAddApp::onChoose()
{
    std::string app = ui->comboBox->currentText().toStdString();
    
    QDataModel::proxyList const & apps = DataModel::getInstance()->getApps();
    
    utils::attributes a = apps.find(app)->second.begin()->second;
    
    proxySettings[app] = a;
    
    mainWindow->onAddApplication(ui->comboBox->currentText());
    
}

DialogAddApp::~DialogAddApp()
{
    delete ui;
}
