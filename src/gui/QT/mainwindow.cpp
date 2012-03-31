#include "appsettings.h"
#include "proxysettings.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddnetwork.h"
#include "applicationsettingstab.h"
#include "dialogabout.h"

using namespace utils;

/*** Init ***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Init data model
    DataModel::getInstance(this);
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
    connect(DataModel::getInstance(), SIGNAL(onAddAppSettings(utils::AppSettings)),
            this, SLOT(onAddApplicationSettings(utils::AppSettings)));
    // end data model connection
    
    bindData();
    
}

void MainWindow::bindData()
{
     DataModel::ProxyList const & proxies = DataModel::getInstance()->getProxies();
     for(int i = 0; i < proxies.size(); i++) {
         ui->listWidgetNetworks->addItem("Some network");
         //ui->listWidgetNetworks->addItem(
         //            proxies.at(i).getAllSettings().at());
     }
}

/*** Data model reactions ***/
void MainWindow::onAddApplicationSettings(utils::AppSettings const& appSettings)
{
    ui->tabWidget->addTab(
                    new ApplicationSettingsTab(appSettings, ui->tabWidget), 
                    //QString(appSettings.getApplicationName().data())
                    "Some appSettings"
                );
}

/*** Front end slots ***/
void MainWindow::addNetwork()
{
    DialogAddNetwork* aDialog = new DialogAddNetwork(this);
    aDialog->show();
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
