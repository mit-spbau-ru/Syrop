#include "datamodel.h"

void QDataModel::addApplicationSettings(std::string const & title){
    
    emit onAddApplicationSettings(title);
    
}

