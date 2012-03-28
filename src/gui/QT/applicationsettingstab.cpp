#include "applicationsettingstab.h"
#include "ui_applicationsettingstab.h"

ApplicationSettingsTab::ApplicationSettingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationSettingsTab)
{
    ui->setupUi(this);
    //ui->formLayout->
}

ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}
