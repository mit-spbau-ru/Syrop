#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddnetwork.h"
#include "applicationsettingstab.h"

/*** Init ***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    ui->horizontalLayoutHolder->setMargin(10);
    ui->centralwidgetHolder->setLayout(ui->horizontalLayoutHolder);
    
}


/*** Triggers ***/
void MainWindow::addNetwork()
{
    DialogAddNetwork* aDialog = new DialogAddNetwork(this);
    aDialog->show();
}


/*** Event handlers ***/
void MainWindow::addNewApplicationTab(QString const& networkTitle)
{
    ui->listWidgetNetworks->addItem(networkTitle);
    ui->tabWidget->addTab(new ApplicationSettingsTab, networkTitle);
}


/*** Other ***/
MainWindow::~MainWindow()
{
    delete ui;
}
