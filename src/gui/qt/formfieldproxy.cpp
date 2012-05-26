#include "formfieldproxy.h"
#include "ui_formfieldproxy.h"
#include <QStringList>
#include "applicationsettingstab.h"

FormFieldProxy::FormFieldProxy(QWidget *parent) :
    FormPluginField(parent),
    ui(new Ui::FormFieldProxy)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);
}

QString FormFieldProxy::getValue()
{   
    return ui->lineEdit->text() + ":" + ui->spinBox->text();
}

void FormFieldProxy::setName(QString const & value) 
{
    ui->label->setText(value);
}

void FormFieldProxy::setValue(QString const & value) 
{
    QStringList list = value.split(':');
    if(list.size() != 2)
        return;
    ui->lineEdit->setText(list.at(0));
    ui->spinBox->setValue(list.at(1).toInt());
}

void FormFieldProxy::bindToTab(ApplicationSettingsTab * tab)
{
    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            tab, SLOT(onChange()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            tab, SLOT(onChange()));
}

FormFieldProxy::~FormFieldProxy()
{
    delete ui;
}
