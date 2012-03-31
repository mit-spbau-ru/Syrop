#include "applicationsettingstab.h"
#include "ui_applicationsettingstab.h"

ApplicationSettingsTab::ApplicationSettingsTab(
        utils::AppSettings const & appSettings, QWidget *parent) 
    : QWidget(parent)
    , ui(new Ui::ApplicationSettingsTab)
    , appSettings(appSettings)
{
    ui->setupUi(this);
    this->setLayout(ui->formLayout);
    ui->formLayout->setMargin(10);
}

ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}
