#include "ShieldSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../services/PlayerStatsService.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-demo/components/PlayerComponent.h"
ShieldSystem::ShieldSystem(EntityManager &entityManager) : System(entityManager)
{

}

void ShieldSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerComponent>()) {
		auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
		auto& sprite = entity->getComponent<SpriteComponent>();

		if (playerStats.getSHDactive()) {
			sprite.setTexture("characterShield");
		}
	}
}
