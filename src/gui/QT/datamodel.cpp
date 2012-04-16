#include <genutils.h>
#include <map>

#include "datamodel.h"

using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;
string const QDataModel::WORKING_DIRECTORY  = "../res/";

void QDataModel::loadData()
{
    utils::readAllProxySettings(WORKING_DIRECTORY, proxySettings);
    
    //proxySettings[name].save(utils::fileNameFromNet());
    
    emit onLoadData();
}

// TODO: check file name and throw exceptin if bad 
// or in proxySettings there exists same name
// file bad if it couldn't be saved in file sysytem
void QDataModel::addNetwork(QString const & name)
{
    ProxySettings p(name.toStdString());
    proxySettings.insert(make_pair(name.toStdString(), p));
    
    emit onAddNetwork(name);
}

void QDataModel::removeNetwork(const QString &name)
{
    proxySettings::iterator it = proxySettings.find(name.toStdString());
    proxySettings.erase(it);
    
    emit onRemoveNetwork(name);
    
}






