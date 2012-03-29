#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddnetwork.h"
#include "applicationsettingstab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    ui->horizontalLayoutHolder->setMargin(10);
    ui->centralwidgetHolder->setLayout(ui->horizontalLayoutHolder);
    
    connect(ui->pushButtonNetworkAdd, SIGNAL(clicked()),
            this, SLOT(addNetwork()));
    
    connect(ui->actionAddNetwork, SIGNAL(triggered(bool)), 
            this, SLOT(addNetwork()));
    
    ui->tabWidget->addTab(new ApplicationSettingsTab, "New tab");
    
    
}

void MainWindow::addNetwork()
{
    DialogAddNetwork* aDialog = new DialogAddNetwork(this);
    
    if (aDialog->exec()) {
        QString title = aDialog->getTitle();
        addNetworkEntity(title);
    }
}

void MainWindow::addNetworkEntity(QString const& networkTitle)
{
    ui->listWidgetNetworks->addItem(networkTitle);
    QWidget* q = new QWidget;
    ui->tabWidget->addTab(q, networkTitle);
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
