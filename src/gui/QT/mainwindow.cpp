#include "proxysettings.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddnetwork.h"
#include "applicationsettingstab.h"
#include "dialogabout.h"

#include <vector>


using namespace utils;
using namespace std;

/*** Init ***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Init data model
    DataModel::createInstance(this);
    connect(DataModel::getInstance(), SIGNAL(onLoadData()),
            this, SLOT(onLoad()));
    DataModel::getInstance()->loadData();
}

void MainWindow::onLoad()
{
    // design settings
    ui->setupUi(this);
    ui->horizontalLayoutHolder->setMargin(10);
    ui->centralwidgetHolder->setLayout(ui->horizontalLayoutHolder);
    // end design settings
    
    // front end connections
    connect(ui->pushButtonNetworkAdd, SIGNAL(clicked()), 
            this, SLOT(addNetwork()));
    connect(ui->actionAddNetwork, SIGNAL(triggered(bool)), 
            this, SLOT(addNetwork()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)),
            this, SLOT(showAbout()));
    // end front end connection
    
    // data model connections
    disconnect(DataModel::getInstance(), SIGNAL(onLoadData()),
            this, SLOT(onLoad()));
    connect(DataModel::getInstance(), SIGNAL(onAddNetwork(QString)),
            this, SLOT(onAddNetwork(QString)));
    // end data model connection
    
    
    bindData();
    
    // select first network
    if(DataModel::getInstance()->getProxies().size() > 0){
        ui->listWidgetNetworks->setCurrentRow(0);
    }
    

}

void MainWindow::bindData()
{
     DataModel::ProxyList const & proxies = DataModel::getInstance()->getProxies();
     
     for(int i = 0; i < proxies.size(); i++) {
         ui->listWidgetNetworks->addItem("GIVE ME NAME");
     }
     connect(ui->listWidgetNetworks,SIGNAL(currentRowChanged(int)),
             this, SLOT(changeCurrentNetwork(int)));
}

/*** Data model reactions ***/
void MainWindow::onAddNetwork(QString const & title)
{    
    ui->listWidgetNetworks->addItem(title);
}

/*** Front end slots ***/
void MainWindow::addNetwork()
{
    DialogAddNetwork* aDialog = new DialogAddNetwork(this);
    aDialog->show();
}
void MainWindow::changeCurrentNetwork(int i)
{
    ProxySettings proxySettings = DataModel::getInstance()->getProxies().at(i);
    ui->tabWidget->clear();
    ProxySettings::iterator it = proxySettings.begin();
    while(it != proxySettings.end()) {
        ui->tabWidget->addTab(new ApplicationSettingsTab(ui->tabWidget, it->second), 
                              QString(it->first.data()));
        it++;
    }
}

void MainWindow::showAbout()
{
    DialogAbout d;
    d.exec();
}

/*** Other ***/
MainWindow::~MainWindow()
{
    delete ui;
}

