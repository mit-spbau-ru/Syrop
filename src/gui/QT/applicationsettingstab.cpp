#include "applicationsettingstab.h"
#include "ui_applicationsettingstab.h"
#include <QLineEdit>

ApplicationSettingsTab::ApplicationSettingsTab(QWidget *parent, utils::attributes const& attributes) 
    : QWidget(parent)
    , ui(new Ui::ApplicationSettingsTab)
    , attributes(attributes)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->widget->setLayout(ui->formLayout);
    ui->formLayout->setMargin(10);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    
    for(utils::attributes::const_iterator it =  attributes.begin(); 
        it != attributes.end(); ++it) 
    {
        QString const key(it->first.data());
        QString const value(it->second.data());
        QLineEdit* const le = new QLineEdit(this);
        le->setText(value);
        ui->formLayout->addRow(key, le);
    }
    
    ui->widget->setFixedHeight(ui->formLayout->sizeHint().height());
    ui->scrollArea->setWidget(ui->widget);
    
}

ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}
