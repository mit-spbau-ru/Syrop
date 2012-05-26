#ifndef FORMPLUGINFIELD_H
#define FORMPLUGINFIELD_H

#include <QString>
#include <QWidget>

class ApplicationSettingsTab;

struct FormPluginField: public QWidget
{
    

    FormPluginField(QWidget *parent = 0)
        :QWidget(parent) {}
    
    // TODO: make it const
    virtual QString getValue() = 0;
    virtual void setValue(QString const & value) = 0;
    virtual void setName(QString const & value) = 0;
    virtual void bindToTab(ApplicationSettingsTab*){}

    
};

#endif // FORMPLUGINFIELD_H
