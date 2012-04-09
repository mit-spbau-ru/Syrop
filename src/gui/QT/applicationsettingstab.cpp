#include "applicationsettingstab.h"
#include "ui_applicationsettingstab.h"

ApplicationSettingsTab::ApplicationSettingsTab(QWidget *parent, utils::attributes& attributes) 
    : QWidget(parent)
    , ui(new Ui::ApplicationSettingsTab)
    , attributes(attributes)
{
    ui->setupUi(this);
    this->setLayout(ui->formLayout);
    ui->formLayout->setMargin(10);
    
    utils::attributes::iterator it = attributes.begin();
    
    
    while(it != attributes.end()) {
        QString key(it->first.data());
        QString value(it->second.data());
        QLineEdit* le = new QLineEdit(this);
        le->setText(value);
        ui->formLayout->addRow(key, le);
        it++;
    }
    
}

ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}
