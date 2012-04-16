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
    
    
    
    emit onLoadData();
}

// TODO: check file name and throw exceptin if bad 
// or in proxySettings there exists same name
// file bad if it couldn't be saved in file sysytem
void QDataModel::addNetwork(QString const & name)
{
    proxySettings.insert(make_pair(name.toStdString(), ProxySettings()));
    emit onAddNetwork(name);
}






