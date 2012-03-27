#ifndef APPLICATIONSETTINGSTAB_H
#define APPLICATIONSETTINGSTAB_H

#include <QWidget>

namespace Ui {
class ApplicationSettingsTab;
}

class ApplicationSettingsTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit ApplicationSettingsTab(QWidget *parent = 0);
    ~ApplicationSettingsTab();
    
private:
    Ui::ApplicationSettingsTab *ui;
};

#endif // APPLICATIONSETTINGSTAB_H
