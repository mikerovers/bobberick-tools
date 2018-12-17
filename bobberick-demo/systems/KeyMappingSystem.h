#ifndef BOBBERICK_TOOLS_KEYMAPPINGSYSTEM_H
#define BOBBERICK_TOOLS_KEYMAPPINGSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/services/SaveService.h"

class KeyMappingSystem : public System
{
public:
	explicit KeyMappingSystem(EntityManager& entityManager);
	void update() override;
	~KeyMappingSystem() = default;
	
	bool isKeyTaken(SDL_Scancode key);

private:
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	SettingsService& settings = ServiceManager::Instance()->getService<SettingsService>();
	InputHandler& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	SaveService& save = ServiceManager::Instance()->getService<SaveService>();
};

#endif //BOBBERICK_TOOLS_KEYMAPPINGSYSTEM_H