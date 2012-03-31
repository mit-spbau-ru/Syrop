#ifndef APPLICATIONSETTINGSTAB_H
#define APPLICATIONSETTINGSTAB_H

#include <QWidget>
#include "appsettings.h"

namespace Ui {
class ApplicationSettingsTab;
}

class ApplicationSettingsTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit ApplicationSettingsTab(utils::AppSettings const & appSettings, 
                                    QWidget *parent = 0 );
    
    ~ApplicationSettingsTab();
    
private:
    Ui::ApplicationSettingsTab *ui;
    utils::AppSettings const & appSettings;
    void bindData();
};

#endif // APPLICATIONSETTINGSTAB_H
