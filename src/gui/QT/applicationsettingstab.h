#ifndef APPLICATIONSETTINGSTAB_H
#define APPLICATIONSETTINGSTAB_H

#include <QWidget>


namespace Ui { class ApplicationSettingsTab;}

/**
 * Contains appliacation settings as tab
 */
class ApplicationSettingsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationSettingsTab( QWidget *parent = 0 );
    ~ApplicationSettingsTab();
private:
    Ui::ApplicationSettingsTab *ui;
    
    void bindData();
};

#endif // APPLICATIONSETTINGSTAB_H
