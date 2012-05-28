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
#include "inidata.h"
#include "coreutils.h"

/**
 * Main data structure with events
 */
class QDataModel : public QObject
{
    Q_OBJECT
    friend class DataModel;
public:
    typedef std::map<std::string, utils::ProxySettings> proxyList;
    static std::string const NETWORK_SETTINGS_FILE;
    
    proxyList& getProxies() { return proxySettings; }
    utils::plugins_t const & getApps() const { return pluginsList; }

public slots:
    void loadData();
    void loadDataNetworkSettings();
    
    void addNetwork(QString const & name);
    void removeNetwork(QString const & name);
    void updateNetwork(QString const & name);
    void restoreNetwork(std::string const & name);
    utils::attributes loadPluginSettings(QString const & name);
    utils::attributes loadNetworkSettings(QString const & name);
    void saveNetworkSettings(QString const & name, utils::attributes const & attrs);
    void removeNetworkSettings(QString const & name);
    
signals:
    void onLoadData();
    void onAddNetwork(QString const & name);
    void onRemoveNetwork(QString const & name);
    void onUpdateNetwork(QString const & name);
    
private:
    proxyList proxySettings;
    utils::plugins_t pluginsList;
    QDataModel(QObject *parent = 0) 
        : QObject(parent)
        , proxySettings(proxyList())
        , pluginsList(utils::plugins_t())
    {}
    QDataModel(QDataModel const &);
    void operator=(QDataModel const &);
    utils::IniData networksSettingsMapping;
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
        if(parent == 0) {
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
