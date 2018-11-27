#include "CheatSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../components/PlayerStatsComponent.h"

CheatSystem::CheatSystem(EntityManager& entityManager) : System(entityManager)
{
}

void CheatSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>())
	{
		handleKeyInput(entity);
	}
}

void CheatSystem::handleKeyInput(Entity* entity)
{
	auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	auto& playerStats = entity->getComponent<PlayerStatsComponent>();

	if (inputHandler.isKeyDown(SDL_SCANCODE_GRAVE))
	{
		if (inputHandler.isKeyDown(SDL_SCANCODE_G)) { // Get max gold
			playerStats.gold = 999999;
		} else if (inputHandler.isKeyDown(SDL_SCANCODE_E)) { // Get max experience
			playerStats.xp = 999999;
		} else if (inputHandler.isKeyDown(SDL_SCANCODE_H)) { // Get max health
			playerStats.changeHPmax(999999);
			playerStats.healPercent(100);
		} else if (inputHandler.isKeyDown(SDL_SCANCODE_M)) { // Get a 10 second shield (M for mode)
			playerStats.shdTime = 600;
			if (!playerStats.shieldActive()) {
				playerStats.toggleShield();
			}
		} else if (inputHandler.isKeyDown(SDL_SCANCODE_P)) { // Add 1000 attack power
			playerStats.changeATmin(1000);
			playerStats.changeATmax(1000);
		}
	}

	
}