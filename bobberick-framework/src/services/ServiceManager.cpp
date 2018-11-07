#include "ServiceManager.h"

ServiceManager* ServiceManager::instance = nullptr;

ServiceManager *ServiceManager::Instance()
{
    if (instance == nullptr) {
        instance = new ServiceManager();
    }

    return instance;
}

void ServiceManager::clean()
{
    // TODO implement if needed.
}
