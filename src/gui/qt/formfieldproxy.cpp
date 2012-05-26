#include "formfieldproxy.h"
#include "ui_formfieldproxy.h"
#include <QStringList>

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

FormFieldProxy::~FormFieldProxy()
{
    delete ui;
}
