#include <genutils.h>
#include <map>

#include "datamodel.h"

#include <iostream>

using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;

void QDataModel::loadData()
{
    proxySettings = utils::readAllProxySettings("../res");
    
    ProxySettings pr = proxySettings.begin()->second;
    ProxySettings::iterator it = pr.begin();
    
    while(it != pr.end()) {
        cout << it->first << endl;
        it++;
    }
    
    emit onLoadData();
    
}

void QDataModel::addNetwork(QString const & appName)
{
    //proxySettings.push_back(ProxySettings());
    proxySettings.insert(make_pair(appName.toStdString(), ProxySettings()));
    emit onAddNetwork(appName);
}






