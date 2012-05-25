#include "dialogeditnetwork.h"
#include "ui_dialogeditnetwork.h"
#include "qmessagebox.h"
#include "datamodel.h"
#include <string>

DialogEditNetwork::DialogEditNetwork(QWidget *parent, const QString &networkName)
    : QDialog(parent)
    , ui(new Ui::DialogEditNetwork)
    , networkName(networkName)
    , isEdited(false)
{
    ui->setupUi(this);
    
    ui->verticalLayout->setMargin(10);
    this->setLayout(ui->verticalLayout);
    
    attrs = DataModel::getInstance()->loadNetworkSettings(networkName);
    std::string sum = "";
    for(utils::attributes::iterator it = attrs.begin(); 
        it != attrs.end(); it++) {
        sum.append(it->first + "=" + it->second + "\n");
    }
            
    ui->plainTextEditNetworkSettings->setPlainText(QString(sum.c_str()));
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
    DataModel::getInstance()->saveNetworkSettings();
    isEdited = false;
}

DialogEditNetwork::~DialogEditNetwork()
{
    delete ui;
}
