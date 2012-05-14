#ifndef APPLICATIONSETTINGSTAB_H
#define APPLICATIONSETTINGSTAB_H

#include "mainwindow.h"

#include <QWidget>
#include <inidata.h>
#include <qmap.h>
#include <qlineedit.h>


namespace Ui { class ApplicationSettingsTab; }

/**
 * Contains appliacation settings as tab
 */
class ApplicationSettingsTab : public QWidget
{
    Q_OBJECT
public:
    
    explicit ApplicationSettingsTab(
            MainWindow* mainWindow,
            QWidget *parent, 
            utils::attributes& attributes);
    ~ApplicationSettingsTab();
    void saveChanges();
private slots:
    void onChange();
private:
    MainWindow* mainWindow;
    QMap<std::string, QLineEdit*> fields;
    Ui::ApplicationSettingsTab *ui;
    utils::attributes& attributes;
    
    void bindData();
};

#endif // APPLICATIONSETTINGSTAB_H
