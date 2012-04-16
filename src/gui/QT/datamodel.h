#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QVector>

#include <string>
#include <vector>
#include <stdexcept>
#include <map>

#include "proxysettings.h"
#include "system.h"

/**
 * Main data structure with events
 */
class QDataModel : public QObject
{
    Q_OBJECT
    friend class DataModel;
public:
    typedef std::map<std::string, utils::ProxySettings> proxyList;
    typedef std::map<std::string, std::string> proxyListFileNames;
    static std::string const WORKING_DIRECTORY;
    
    // maybe const ?
    proxyList& getProxies() { return proxySettings; }

public slots:
    void loadData();
    void addNetwork(QString const & name);
    void removeNetwork(QString const & name);
    
signals:
    void onLoadData();
    void onAddNetwork(QString const & appName);
    void onRemoveNetwork(QString const & appName);
    
private:
    proxyList proxySettings;
    proxyListFileNames proxySettingsFileNames;
    QDataModel(QObject *parent = 0) 
        : QObject(parent)
        , proxySettings(proxyList())
    {}
    QDataModel(QDataModel const &);
    void operator=(QDataModel const &);
};


/**
  * Proxy class for storing pointer.
  */
class DataModel
{
public:
    
    static QDataModel* createInstance(QObject* parent)
    {        
        if(instance != 0) {
            throw std::runtime_error("Instance has been created before.");
        }
        if(!parent) {
            throw std::invalid_argument("QDataModel must have non-null parent.");
        }
        instance = new QDataModel(parent);
        return instance;
    }
    
    static QDataModel* getInstance() 
    {
        return instance;
    }

private:
    static QDataModel* instance;
    
};



#endif // DATAMODEL_H
