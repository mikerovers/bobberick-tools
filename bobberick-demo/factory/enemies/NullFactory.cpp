#include "NullFactory.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"

Entity &NullFactory::getEnemy(const int level)
{
    return ServiceManager::Instance()->getService<EntityManager>().addEntity();
}

Entity &NullFactory::getEnemy(const int level, const int spawnerId)
{
    return ServiceManager::Instance()->getService<EntityManager>().addEntity();
}
