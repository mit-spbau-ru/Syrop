#include "formfieldauth.h"
#include "ui_formfieldauth.h"
#include "applicationsettingstab.h"

FormFieldAuth::FormFieldAuth(QWidget *parent) :
    FormPluginField(parent),
    ui(new Ui::FormFieldAuth)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    
}

QString FormFieldAuth::getValue()
{       
    return ui->lineEdit->text() + ":" + ui->lineEdit_2->text();
}

void FormFieldAuth::setName(QString const & ) {}

void FormFieldAuth::setValue(QString const & value) 
{
    QStringList list = value.split(':');
    if(list.size() != 2)
        return;
    ui->lineEdit->setText(list.at(0));
    ui->lineEdit_2->setText(list.at(1));
}


void FormFieldAuth::bindToTab(ApplicationSettingsTab * tab)
{
    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            tab, SLOT(onChange()));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)),
            tab, SLOT(onChange()));
}

FormFieldAuth::~FormFieldAuth()
{
    delete ui;
}
