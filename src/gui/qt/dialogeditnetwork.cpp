#include "dialogeditnetwork.h"
#include "ui_dialogeditnetwork.h"
#include "qmessagebox.h"
#include "datamodel.h"


DialogEditNetwork::DialogEditNetwork(QWidget *parent, const QString &networkName)
    : QDialog(parent)
    , ui(new Ui::DialogEditNetwork)
    , networkName(networkName)
    , isEdited(false)
{
    ui->setupUi(this);
    
    ui->verticalLayout->setMargin(10);
    this->setLayout(ui->verticalLayout);
    
    ui->plainTextEditNetworkSettings->setPlainText(
                DataModel::getInstance()->loadNetworkSettings(networkName));
    connect(ui->plainTextEditNetworkSettings, SIGNAL(textChanged()),
            this, SLOT(onChanged()));  
    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(onSave()));
}

void DialogEditNetwork::onChanged()
{
    isEdited = true;
}


void DialogEditNetwork::onSave()
{
    DataModel::getInstance()->saveNetworkSettings(
                networkName, 
                ui->plainTextEditNetworkSettings->toPlainText());
    isEdited = false;
}

DialogEditNetwork::~DialogEditNetwork()
{
    delete ui;
}
