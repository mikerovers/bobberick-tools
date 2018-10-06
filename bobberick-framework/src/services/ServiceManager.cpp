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
    for(const auto &service : services) {
        service->clean();
        //TODO Delete service from memory.
    }
}
