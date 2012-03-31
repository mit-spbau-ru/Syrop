#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddnetwork.h"
#include "applicationsettingstab.h"

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
    // end front end connection
    
    // data model connections
    disconnect(DataModel::getInstance(), SIGNAL(onLoadData()),
            this, SLOT(onLoad()));
    connect(DataModel::getInstance(), SIGNAL(onAddApplicationSettings(std::string)),
            this, SLOT(onAddApplicationSettings(std::string)));
    // end data model connection
}

/*** Data model reactions ***/
void MainWindow::onAddApplicationSettings(utils::AppSettings const& appSettings)
{
    
    ui->tabWidget->addTab(
                    new ApplicationSettingsTab(appSettings, ui->tabWidget), 
                    QString(appSettings.getApplicationName().data())
                );
    
}

/*** Front end slots ***/
void MainWindow::addNetwork()
{
    DialogAddNetwork* aDialog = new DialogAddNetwork(this);
    aDialog->show();
}

/*** Other ***/
MainWindow::~MainWindow()
{
    delete ui;
}
