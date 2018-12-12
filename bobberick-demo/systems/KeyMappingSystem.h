#ifndef BOBBERICK_TOOLS_KEYMAPPINGSYSTEM_H
#define BOBBERICK_TOOLS_KEYMAPPINGSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"

class KeyMappingSystem : public System
{
public:
	void update() override;

private:
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	SettingsService& settings = ServiceManager::Instance()->getService<SettingsService>();
	InputHandler& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	int skipForRepeat = 0;
};

#endif //BOBBERICK_TOOLS_KEYMAPPINGSYSTEM_H