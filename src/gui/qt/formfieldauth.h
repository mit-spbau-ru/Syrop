#ifndef FORMFIELDAUTH_H
#define FORMFIELDAUTH_H

#include <QWidget>
#include "formpluginfield.h"

namespace Ui {
class FormFieldAuth;
}

class FormFieldAuth : public FormPluginField
{
    Q_OBJECT
    
public:
    explicit FormFieldAuth(QWidget *parent = 0);
    ~FormFieldAuth();
    
    QString getValue();
    void setValue(QString const & value);
    void setName(QString const & value);
    
private:
    Ui::FormFieldAuth *ui;
};

#endif // FORMFIELDAUTH_H
