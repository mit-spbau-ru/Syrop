#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogaddnetwork.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    
    ui->setupUi(this);
    ui->centralwidgetHolder->setLayout(ui->horizontalLayoutHolder);
    
    connect(ui->pushButtonNetworkAdd, SIGNAL(clicked()),
            this, SLOT(addNetwork()));
    
    connect(ui->actionAddNetwork, SIGNAL(triggered(bool)), 
            this, SLOT(addNetwork()));
    
}

void MainWindow::addNetwork()
{
    DialogAddNetwork aDialog;
    if (aDialog.exec()) {
        QString title = aDialog.getTitle();
        addNetworkEntity(title);
    }
}

void MainWindow::addNetworkEntity(QString const& networkTitle)
{
    ui->listWidgetNetworks->addItem(networkTitle);
    QWidget* q = new QWidget;
    ui->tabWidget->addTab(q, "**** Tab");
    
    
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
