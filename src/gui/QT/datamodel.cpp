#include <genutils.h>
#include <map>

#include "datamodel.h"

using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;
string const QDataModel::WORKING_DIRECTORY  = "../res/";

void QDataModel::loadData()
{
    readAllProxySettings(WORKING_DIRECTORY, proxySettings);
    
    emit onLoadData();
}

// TODO: check file name and throw exceptin if bad 
// or in proxySettings there exists same name
// file bad if it couldn't be saved in file sysytem
void QDataModel::addNetwork(QString const & name)
{
    string stdName = name.toStdString();
    ProxySettings p;
    proxySettings.insert(make_pair(stdName, p));
    p.save(WORKING_DIRECTORY + fileNameFromNet(stdName));
    
    emit onAddNetwork(name);
}

void QDataModel::removeNetwork(const QString &name)
{
    
    proxyList::iterator it = proxySettings.find(name.toStdString());
    utils::remove_file(WORKING_DIRECTORY + fileNameFromNet(name.toStdString()));
    proxySettings.erase(it);
    
    emit onRemoveNetwork(name);
    
}






