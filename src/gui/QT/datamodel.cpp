#include <stdexcept>
#include <map>

#include <genutils.h>

#include "datamodel.h"
#include "coreutils.h"


using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;
string const QDataModel::WORKING_DIRECTORY  = "~/.syrop/res/";
string const QDataModel::CONFIG_DIRECTORY  = "~/.syrop/config/";
string const QDataModel::APPS_DIRECTORY  = "~/.syrop/config/apps/";
string const QDataModel::DEFAULT_NETWORK_CONFIG_PATH  = "~/.syrop/config/default";
string const QDataModel::DEFAULT_SETTINGS_NAME = "~/.syrop/default";


void QDataModel::loadData()
{
    readAllProxySettings(WORKING_DIRECTORY, proxySettings);
    readAllProxySettings(APPS_DIRECTORY, appsList);
    
    emit onLoadData();
}

void QDataModel::restoreNetwork(const string &name)
{
    proxySettings.find(name)->second.loadData(
                WORKING_DIRECTORY + fileNameFromNet(name));
}

void QDataModel::addNetwork(QString const & name)
{
    
    string stdName = name.toStdString();
    if(proxySettings.find(stdName) != proxySettings.end()) {
        throw invalid_argument("There exists network with same name.");
    }
    
    ProxySettings p;
    p.loadData(DEFAULT_NETWORK_CONFIG_PATH);
    p.save(WORKING_DIRECTORY + fileNameFromNet(stdName));
    
    proxySettings.insert(make_pair(stdName, p));
    
    emit onAddNetwork(name);
}

void QDataModel::updateNetwork(const QString &name)
{
    string stdName = name.toStdString();
    proxySettings[stdName].save(WORKING_DIRECTORY + fileNameFromNet(stdName));
    
    emit onUpdateNetwork(name);
}

void QDataModel::removeNetwork(const QString &name)
{
    proxyList::iterator it = proxySettings.find(name.toStdString());
    utils::remove_file(WORKING_DIRECTORY + fileNameFromNet(name.toStdString()));
    proxySettings.erase(it);
    
    emit onRemoveNetwork(name);
}






