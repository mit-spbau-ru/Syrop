#include "dialogaddnetwork.h"
#include "ui_dialogaddnetwork.h"

DialogAddNetwork::DialogAddNetwork(QWidget *parent) 
    : QDialog(parent)
    , ui(new Ui::DialogAddNetwork)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(10);
    this->setLayout(ui->verticalLayout);
    connect(ui->buttonBox, SIGNAL(accepted()), 
            this, SLOT(onSubmitChanges()));
}

void DialogAddNetwork::onSubmitChanges()
{
    DataModel::getInstance()->addAppSettings("Hellooooo");
    this->close();
}

DialogAddNetwork::~DialogAddNetwork()
{
    delete ui;
}
