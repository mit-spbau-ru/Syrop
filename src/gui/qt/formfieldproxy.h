#ifndef FORMFIELDPROXY_H
#define FORMFIELDPROXY_H

#include <QWidget>
#include "formpluginfield.h"

namespace Ui {
class FormFieldProxy;
}

class FormFieldProxy : public FormPluginField
{
    Q_OBJECT
    
public:
    explicit FormFieldProxy(QWidget *parent = 0);
    ~FormFieldProxy();
    
    QString getValue();
    void setValue(QString const & value);
    void setName(QString const & value);
    

    
    
private:
    Ui::FormFieldProxy *ui;
};

#endif // FORMFIELDPROXY_H
