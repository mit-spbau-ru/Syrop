#include "applicationsettingstab.h"
#include "ui_applicationsettingstab.h"
#include <QLineEdit>
#include "formfieldproxy.h"
#include "formfieldauth.h"
#include "formfieldtext.h"
#include "stdexcept"

ApplicationSettingsTab::ApplicationSettingsTab(
        MainWindow* mainWindow,
        QWidget* parent, 
        utils::attributes& attributes,
        utils::attributes const & pluginFields)
    : QWidget(parent)
    , mainWindow(mainWindow)
    , ui(new Ui::ApplicationSettingsTab)
    , attributes(attributes)
    , pluginFields(pluginFields)
{
    ui->setupUi(this);
      this->setLayout(ui->verticalLayout);
      ui->widget->setLayout(ui->formLayout);
      ui->formLayout->setMargin(10);
      ui->scrollArea->setFrameShape(QFrame::NoFrame);
      
      for(utils::attributes::const_iterator it =  pluginFields.begin(); 
          it != pluginFields.end(); ++it) 
      {
          QString type(it->second.data());
          FormPluginField* p = fieldsFactory(type);
          ui->formLayout->addWidget(p);
          
          QString key(it->first.data());
          p->setName(key);
          fields[key] = p;
          if(attributes.find(it->first.data()) != attributes.end()) {
             QString value = attributes.find(it->first.data())->second.data();
             p->setValue(value);
          }
          p->bindToTab(this);
          
      }
      
      ui->widget->setFixedHeight(ui->formLayout->sizeHint().height());
      ui->scrollArea->setWidget(ui->widget);
}

void ApplicationSettingsTab::onChange()
{
    mainWindow->onCurrentNetworkEdited();
}

void ApplicationSettingsTab::saveChanges()
{
    QMapIterator<QString, FormPluginField*> i(fields);
    while (i.hasNext()) {
        i.next();
        attributes[i.key().toStdString()] = i.value()->getValue().toStdString();
    }
}

FormPluginField* ApplicationSettingsTab::fieldsFactory(QString const & type)
{
    
    if(type == "proxy") {
        return new FormFieldProxy(this);
    }
    if(type == "auth") {
        return new FormFieldAuth(this);
    }
    if(type == "text") {
        return new FormFieldText(this);
    }
        
    throw std::logic_error("undefined type");
    

}


ApplicationSettingsTab::~ApplicationSettingsTab()
{
    delete ui;
}

