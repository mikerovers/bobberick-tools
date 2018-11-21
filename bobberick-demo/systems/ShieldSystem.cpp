#include "ShieldSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"
ShieldSystem::ShieldSystem(EntityManager &entityManager) : System(entityManager)
{

}

void ShieldSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>()) {
		auto& playerStats = entity->getComponent<PlayerStatsComponent>();
		auto& sprite = entity->getComponent<SpriteComponent>();

		if (playerStats.shieldActive()) {
			sprite.setTexture("characterShield");
		}
	}
}
