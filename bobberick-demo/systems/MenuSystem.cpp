#include "MenuSystem.h"
#include "../../bobberick-demo/components/AdvertisementComponent.h"
#include "../../bobberick-demo/components/ButtonSettingComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include <sstream>

MenuSystem::MenuSystem(EntityManager &entityManager) : System(entityManager)
{

}

void MenuSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<ButtonSettingComponent>()) {
		if (entity->hasComponent<ButtonSpriteComponent>()) {
			auto& buttonSettingComponent = entity->getComponent<ButtonSettingComponent>();
			auto& spriteComponent = entity->getComponent<ButtonSpriteComponent>();
			if (buttonSettingComponent.getSetting() == "music") {
				if (ServiceManager::Instance()->getService<SettingsService>().music) {
					spriteComponent.setTexture("blankGreenButton");
				}
				else {
					spriteComponent.setTexture("blankRedButton");
				}
			}
		}
	}
}
