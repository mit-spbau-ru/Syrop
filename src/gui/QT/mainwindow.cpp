#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddnetwork.h"
#include "applicationsettingstab.h"

/*** Init ***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Init model
    DataModel::getInstance(this);
    
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
    connect(DataModel::getInstance(), SIGNAL(onAddApplicationSettings(std::string)),
            this, SLOT(onAddApplicationSettings(std::string)));
    // end data model connection
    
}


/*** Front end slots ***/
void MainWindow::addNetwork()
{
    DialogAddNetwork* aDialog = new DialogAddNetwork(this);
    aDialog->show();
}


/*** Data model reactions***/
void MainWindow::onAddApplicationSettings(std::string const& networkTitle)
{
    QString str(networkTitle.data());
    ui->listWidgetNetworks->addItem(str);
    ui->tabWidget->addTab(new ApplicationSettingsTab, str);
}


/*** Other ***/
MainWindow::~MainWindow()
{
    delete ui;
}
