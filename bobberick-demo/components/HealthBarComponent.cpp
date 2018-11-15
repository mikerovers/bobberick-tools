#include "HealthBarComponent.h"
#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"

void HealthBarComponent::init()
{

}

HealthBarComponent::HealthBarComponent() :
outerBox(ServiceManager::Instance()->getService<EntityManager>().addEntity()),
innerBox(ServiceManager::Instance()->getService<EntityManager>().addEntity()),
healthBox(ServiceManager::Instance()->getService<EntityManager>().addEntity())
{

}

