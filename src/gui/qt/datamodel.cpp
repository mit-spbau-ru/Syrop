#include <stdexcept>
#include <map>
#include <genutils.h>
#include <fstream>
#include <qtextstream.h>

#include "datamodel.h"
#include "coreutils.h"
#include "namedb2.h"
#include "iniparser.h"

using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;
string const QDataModel::NETWORK_SETTINGS_FILE  = 
    utils::application_dir() + utils::MAPPING_FILE;
string const QDataModel::CONFIG_DIRECTORY   = "../config/";
string const QDataModel::DEFAULT_NETWORK_CONFIG_PATH  = "../config/default";
string const QDataModel::DEFAULT_SETTINGS_NAME = "default";

void QDataModel::loadData()
{
    readAllProxySettings(utils::config_dir(), proxySettings);
    utils::list_plugins(utils::search_pathes(), this->pluginsList);
    loadDataNetworkSettings();
    emit onLoadData();
}

void QDataModel::loadDataNetworkSettings()
{
    ifstream i(NETWORK_SETTINGS_FILE.c_str());
    i >> networksSettingsMapping;
}

void QDataModel::restoreNetwork(const string &name)
{
    proxySettings.find(name)->second.load(
                utils::config_dir() + fileNameFromNet(name));
}

void QDataModel::addNetwork(QString const & name)
{    
    string stdName = name.toStdString();
    if(proxySettings.find(stdName) != proxySettings.end())
        throw invalid_argument("There exists network with same name.");

    ProxySettings p;
    p.load(DEFAULT_NETWORK_CONFIG_PATH);
    p.save(utils::config_dir() + fileNameFromNet(stdName));
    
    proxySettings.insert(make_pair(stdName, p));
    
    emit onAddNetwork(name);
}

void QDataModel::updateNetwork(const QString &name)
{
    string stdName = name.toStdString();
    proxySettings[stdName].save(utils::config_dir() + fileNameFromNet(stdName));
    
    emit onUpdateNetwork(name);
}

void QDataModel::removeNetwork(const QString &name)
{
    proxyList::iterator it = proxySettings.find(name.toStdString());
    utils::remove_file(utils::config_dir() + fileNameFromNet(name.toStdString()));
    proxySettings.erase(it);
    
    emit onRemoveNetwork(name);
}


utils::attributes QDataModel::loadNetworkSettings(const QString &name)
{
    return networksSettingsMapping[name.toStdString()];
}

void QDataModel::saveNetworkSettings(QString const & name, utils::attributes const & attrs)
{
    networksSettingsMapping[name.toStdString()] = attrs;
    ofstream i(NETWORK_SETTINGS_FILE.c_str());
    i << networksSettingsMapping;
}




