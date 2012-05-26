#include "formfieldtext.h"
#include "ui_formfieldtext.h"

FormFieldText::FormFieldText(QWidget *parent) :
    FormPluginField(parent),
    ui(new Ui::FormFieldText)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);
    
}

QString FormFieldText::getValue()
{   
    return ui->lineEdit->text();
}

void FormFieldText::setName(QString const & value) 
{
    ui->label->setText(value);
}

void FormFieldText::setValue(QString const & value) 
{
    ui->lineEdit->setText(value);
}

FormFieldText::~FormFieldText()
{
    delete ui;
}
