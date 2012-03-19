#include "dialogaddnetwork.h"
#include "ui_dialogaddnetwork.h"

DialogAddNetwork::DialogAddNetwork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNetwork)
{
    ui->setupUi(this);
}

QString const& DialogAddNetwork::getTitle() const
{
    return ui->lineEditTitle->text();
}

DialogAddNetwork::~DialogAddNetwork()
{
    delete ui;
}
