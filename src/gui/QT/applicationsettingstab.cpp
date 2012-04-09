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
        
        if(key == "asd"){
        }
        
        QString value(it->second.data());
        ///qDebug();
        it++;
    }
    
}

ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}
