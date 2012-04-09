#include <genutils.h>
#include <map>

#include "datamodel.h"

#include <iostream>

using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;

void QDataModel::loadData()
{
    proxySettings = utils::readAllProxySettings("../res/");
    emit onLoadData();
}

void QDataModel::addNetwork(QString const & name)
{
    //proxySettings.push_back(ProxySettings());
    proxySettings.insert(make_pair(name.toStdString(), ProxySettings()));
    emit onAddNetwork(name);
}






