#include <stdexcept>
#include <map>
#include <genutils.h>
#include <qfile.h>
#include <qtextstream.h>

#include "datamodel.h"
#include "coreutils.h"



using namespace utils;
using namespace std;

QDataModel* DataModel::instance = 0;
string const QDataModel::NETWORK_SETTINGS_DIRECTORY  = "../res/settings/";
string const QDataModel::CONFIG_DIRECTORY   = "../config/";
string const QDataModel::APPS_DIRECTORY     = "../config/apps/";
string const QDataModel::DEFAULT_NETWORK_CONFIG_PATH  = "../config/default";
string const QDataModel::DEFAULT_SETTINGS_NAME = "default";


void QDataModel::loadData()
{
    string s = utils::config_dir();
    readAllProxySettings(utils::config_dir(), proxySettings);
    readAllProxySettings(APPS_DIRECTORY, appsList);
    emit onLoadData();
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

QString QDataModel::getNetworkSettingsFilePath(QString const& name)
{
    return QString((NETWORK_SETTINGS_DIRECTORY + name.toStdString()).c_str());
}

QString QDataModel::loadNetworkSettings(const QString &name)
{
    QFile file(QDataModel::getNetworkSettingsFilePath(name));
    
    if(!file.exists())
        return "";
    if (!file.open(QIODevice::ReadOnly))
        throw runtime_error("Can't open file");
    
    QString sum;
    try {
        QTextStream stream (&file);
        sum = stream.readAll();
    } catch (...) {
        file.close();
        throw runtime_error("Can't read file");
    }
    file.close();
    return sum;
}

void QDataModel::saveNetworkSettings(const QString &name, const QString &content)
{
    QFile file(QDataModel::getNetworkSettingsFilePath(name));
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << content;
    file.close();
}




