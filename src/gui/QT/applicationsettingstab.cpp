#include "applicationsettingstab.h"
#include "ui_applicationsettingstab.h"

ApplicationSettingsTab::ApplicationSettingsTab(QWidget *parent) 
    : QWidget(parent)
    , ui(new Ui::ApplicationSettingsTab)
{
    ui->setupUi(this);
    this->setLayout(ui->formLayout);
    ui->formLayout->setMargin(10);
}

ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}
