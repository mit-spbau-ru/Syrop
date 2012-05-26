#ifndef FORMFIELDTEXT_H
#define FORMFIELDTEXT_H

#include <QWidget>
#include "formpluginfield.h"

namespace Ui {
class FormFieldText;
}

class FormFieldText : public FormPluginField
{
    Q_OBJECT
    
public:
    explicit FormFieldText(QWidget *parent = 0);
    ~FormFieldText();
    
    QString getValue();
    void setValue(QString const & value);
    void setName(QString const & value);
    void bindToTab(ApplicationSettingsTab * tab);

    
private:
    Ui::FormFieldText *ui;
};

#endif // FORMFIELDTEXT_H
