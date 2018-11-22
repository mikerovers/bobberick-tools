#include "DeadSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../components/DeadComponent.h"
#include "../components/StatsComponent.h"
#include "../components/HealthBarComponent.h"
#include "../components/PlayerStatsComponent.h"
#include "../components/EndBossComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../components/AIComponent.h"
#include "../../bobberick-framework/src/services/SoundManager.h"

void DeadSystem::init()
{
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/biem.ogg", "biem",
	                                                            SOUND_SFX);
}

void DeadSystem::update()
{
	auto deadComponentEntities = ServiceManager::Instance()
	                             ->getService<EntityManager>().getAllEntitiesWithComponent<DeadComponent>();

	for (auto&& entity : deadComponentEntities)
	{
		if (entity->hasComponent<StatsComponent>())
		{
			auto statsComponent = entity->getComponent<StatsComponent>();
			auto& deathComponent = entity->getComponent<DeadComponent>();
			if (statsComponent.getHP() <= 0 && !deathComponent.handledDeath)
			{
				ServiceManager::Instance()->getService<SoundManager>().playSound(4, "biem", 0);

				if (entity->hasComponent<EndBossComponent>())
				{
					// win
				}
				for (auto& player : ServiceManager::Instance()
				                    ->getService<EntityManager>().getAllEntitiesWithComponent<PlayerStatsComponent>())
				{
					player->getComponent<PlayerStatsComponent>().xp += entity
					                                                   ->getComponent<StatsComponent>().getHPmax();
				}

				auto& healthBar = entity->getComponent<HealthBarComponent>();
				healthBar.healthBox.destroy();
				healthBar.outerBox.destroy();
				healthBar.innerBox.destroy();
				entity->removeComponent<HealthBarComponent>();

				// do death animation

				entity->destroy();
			}
		}
	}
}
