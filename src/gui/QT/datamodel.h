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

class QDataModel : public QObject
{
    Q_OBJECT
    friend class DataModel;
public:
    void loadData();
    void addApplicationSettings();
signals:
    void onLoadData();
    void onProxyItemAdded();
private:
    QDataModel(QObject *parent = 0) : QObject(parent) {}
    QDataModel(QDataModel const &);
    void operator=(QDataModel const &);
};

/**
  * Proxy class for storing pointer.
  */
class DataModel
{
public:
    static QDataModel* getInstance(QObject* parent = 0) 
    {
        static QDataModel* instance = createInstance(parent);
        return instance;
    }
private:
    static QDataModel* createInstance(QObject* parent)
    {
        if(!parent) {
            throw std::runtime_error("QDataModel must have parent.");
        }
        return new QDataModel(parent);
    }
};



#endif // DATAMODEL_H
