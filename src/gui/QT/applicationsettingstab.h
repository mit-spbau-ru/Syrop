#ifndef APPLICATIONSETTINGSTAB_H
#define APPLICATIONSETTINGSTAB_H

#include <QWidget>
#include <inidata.h>

namespace Ui { class ApplicationSettingsTab;}

/**
 * Contains appliacation settings as tab
 */
class ApplicationSettingsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationSettingsTab(QWidget *parent, utils::attributes& attributes);
    ~ApplicationSettingsTab();
private:
    Ui::ApplicationSettingsTab *ui;
    utils::attributes attributes;
    void bindData();
};

#endif // APPLICATIONSETTINGSTAB_H
