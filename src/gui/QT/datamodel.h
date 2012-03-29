#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <vector>
#include <stdexcept>

#include "appsettings.h"
#include "proxysettings.h"

/**
  * Main data structure with events
  */

class DataModel : public QObject
{
    Q_OBJECT
public:
    
    /**
      * Parent maybe MainWindow. QT parent object will 
      * delete instance
      */
    static DataModel* init(QObject *parent)
    {
        instance = new DataModel(parent);
        return getInstance();
    }
    
    /**
      * Works like singleton, but first thing is init()
      */
    static DataModel* instance()
    {
        if(!instance) {
            throw std::runtime_error("Not initialized DataModel.");
        }
        return instance;
    }
    
    void loadData();
    void addApplicationSettings();
    
signals:
    void onLoadData();
    void onProxyItemAdded();

private:
    DataModel(QObject *parent) : QObject(parent) {}
    
    DataModel(DataModel const &);
    void operator=(DataModel const &);
    
    static DataModel* instance;
    
};

#endif // DATAMODEL_H
