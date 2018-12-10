#include "CheatSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../components/PlayerComponent.h"
#include "../services/PlayerStatsService.h"
#include <SDL.h>

CheatSystem::CheatSystem(EntityManager& entityManager) : System(entityManager)
{
}

void CheatSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerComponent>())
	{
		handleKeyInput(entity);
	}
}

void CheatSystem::handleKeyInput(Entity* entity)
{
	auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	auto&& playerEntities = ServiceManager::Instance()
	                        ->getService<EntityManager>().getAllEntitiesWithComponent<PlayerComponent>();

	auto& playerComponent = playerEntities[0]->getComponent<PlayerComponent>();


	if (inputHandler.isKeyDown(SDL_SCANCODE_GRAVE))
	{
		if (inputHandler.isKeyDown(SDL_SCANCODE_G))
		{
			// Get max gold
			playerStats.gold = 999999;
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_E))
		{
			// Get max experience
			playerStats.xp = 999999;
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_H))
		{
			// Get max health
			playerStats.changeHPmax(999999);
			playerStats.heal(999999);
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_M))
		{
			// Get a 10 second shield (M for mode)
			playerStats.setSHD(600);
			if (!playerStats.getSHDactive())
			{
				playerStats.toggleShield();
			}
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_P))
		{
			// Add 1000 attack power
			playerStats.changeATmin(1000);
			playerStats.changeATmax(1000);
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_EQUALS))
		{
			// set super shooting speed
			playerComponent.shootingTimeout = 10;
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_MINUS))
		{
			// set normal shooting speed
			playerComponent.shootingTimeout = 250;
		}
	}
}
