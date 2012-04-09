#include <genutils.h>
#include <map>

#include "datamodel.h"

using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;

void QDataModel::loadData()
{
    utils::readAllProxySettings("../res/", proxySettings);
    emit onLoadData();
}

void QDataModel::addNetwork(QString const & name)
{
    proxySettings.insert(make_pair(name.toStdString(), ProxySettings()));
    emit onAddNetwork(name);
}






