#include "dialogaddnetwork.h"
#include "ui_dialogaddnetwork.h"

DialogAddNetwork::DialogAddNetwork(QWidget *parent) 
    : QDialog(parent)
    , ui(new Ui::DialogAddNetwork)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(10);
    this->setLayout(ui->verticalLayout);
}

void DialogAddNetwork::submitChanges() const
{
    //return ui->lineEditTitle->text();
}

DialogAddNetwork::~DialogAddNetwork()
{
    delete ui;
}
