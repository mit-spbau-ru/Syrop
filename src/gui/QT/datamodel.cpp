#include <stdexcept>
#include <map>

#include <genutils.h>

#include "datamodel.h"


using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;
string const QDataModel::WORKING_DIRECTORY  = "../res/";
string const QDataModel::CONFIG_DIRECTORY  = "../config/";
string const QDataModel::DEFAULT_NETWORK_CONFIG_PATH  = "../config/default";


void QDataModel::loadData()
{
    readAllProxySettings(WORKING_DIRECTORY, proxySettings);
    
    emit onLoadData();
}

void QDataModel::addNetwork(QString const & name)
{
    
    string stdName = name.toStdString();
    if(proxySettings.find(stdName) != proxySettings.end()) {
        throw invalid_argument("There exists network with same name.");
    }
    ProxySettings p;
    
    //TODO: IT IS VERY BAD!
    p.loadData(DEFAULT_NETWORK_CONFIG_PATH);
    
    proxySettings.insert(make_pair(stdName, p));
    p.save(WORKING_DIRECTORY + fileNameFromNet(stdName));
    
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






