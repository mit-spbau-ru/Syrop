#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>

#include <string>
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
    void addProxyItem(std::string const & title);
    void addAppSettings(QString const & appName);
signals:
    void onLoadData();
    void onAddProxyItem(std::string const & title);
    void onAddAppSettings(utils::AppSettings const & appSettings);
private:
    std::vector<utils::ProxySettings> proxySettings;
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
            throw std::invalid_argument("QDataModel must have parent.");
        }
        return new QDataModel(parent);
    }
};



#endif // DATAMODEL_H
