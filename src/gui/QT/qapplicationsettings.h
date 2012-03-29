#ifndef QAPPLICATIONSETTINGS_H
#define QAPPLICATIONSETTINGS_H

/*
    Represents proxy settings in QT style
*/

#include <QObject>


class QApplicationSettings : public QObject
{
    Q_OBJECT
public:
    explicit QApplicationSettings(QObject *parent = 0);
    
    void LoadData();
    
signals:
    
    void onDataLoaded();
    
public slots:
    
};

#endif // QAPPLICATIONSETTINGS_H
