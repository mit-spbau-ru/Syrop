#include "dialogaddnetwork.h"
#include "ui_dialogaddnetwork.h"

#include <exception>

DialogAddNetwork::DialogAddNetwork(QWidget *parent) 
    : QDialog(parent)
    , ui(new Ui::DialogAddNetwork)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(10);
    ui->labelError->clear();
    this->setLayout(ui->verticalLayout);
    connect(ui->buttonBox, SIGNAL(accepted()), 
            this, SLOT(onSubmitChanges()));
}

void DialogAddNetwork::onSubmitChanges()
{
    try {
        DataModel::getInstance()->addNetwork(ui->lineEditTitle->text());
        this->close();
    } catch (const std::exception& e) {
        ui->labelError->setText(e.what());
    }
}

DialogAddNetwork::~DialogAddNetwork()
{
    delete ui;
}
