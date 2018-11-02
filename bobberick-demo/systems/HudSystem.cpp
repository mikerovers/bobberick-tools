#include "HudSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"

HudSystem::HudSystem(EntityManager &entityManager) : System(entityManager)
{
	
}

void HudSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>()) {
		PlayerStatsComponent& playerStats = entity->getComponent<PlayerStatsComponent>();
		playerStats.update();
		double healthWidth = ((double)playerStats.stats->getHP() / (double)playerStats.stats->getHPmax()) * barWidth;
		double shieldWidth = (playerStats.shdTime / playerStats.shdTimeMax) * barWidth;
		if (playerStats.shieldActive()) { // Brighter blue bar if shield is currently active.
			shieldBox->getComponent<RectangleComponent>().red = 102;
			shieldBox->getComponent<RectangleComponent>().blue = 255;
			shieldBox->getComponent<RectangleComponent>().green = 255;
		} else if (playerStats.shdTime / playerStats.shdTimeMax < 0.5) { // Darker blue bar if shield is not ready to activate.
			shieldBox->getComponent<RectangleComponent>().red = 0;
			shieldBox->getComponent<RectangleComponent>().blue = 153;
			shieldBox->getComponent<RectangleComponent>().green = 51;
		} else { // Blue bar if shield is ready to activate.
			shieldBox->getComponent<RectangleComponent>().red = 0;
			shieldBox->getComponent<RectangleComponent>().blue = 255;
			shieldBox->getComponent<RectangleComponent>().green = 204;
		}
		if (playerStats.shdTime == playerStats.shdTimeMax) { // For testing purposes, delete this!
			playerStats.toggleShield();
		}
		healthBox->getComponent<TransformComponent>().width = healthWidth;
		shieldBox->getComponent<TransformComponent>().width = shieldWidth;
    }
}

void HudSystem::init() 
{
	hudBox = entityManager.addEntity();
	hudBox->addComponent<TransformComponent>(0, 0, 50, 640, 1);
	hudBox->addComponent<RectangleComponent>(51, 51, 204, true);

	outerBox = entityManager.addEntity();
	outerBox->addComponent<TransformComponent>(9, 9, 32, barWidth+2, 1);
	outerBox->addComponent<RectangleComponent>(0, 0, 0, false);

	innerBox = entityManager.addEntity();
	innerBox->addComponent<TransformComponent>(10, 10, 30, barWidth, 1);
	innerBox->addComponent<RectangleComponent>(128, 128, 128, true);

	healthBox = entityManager.addEntity();
	healthBox->addComponent<TransformComponent>(10, 10, 30, barWidth, 1);
	healthBox->addComponent<RectangleComponent>(255, 0, 0, true);

	shieldBox = entityManager.addEntity();
	shieldBox->addComponent<TransformComponent>(10, 35, 5, barWidth, 1);
	shieldBox->addComponent<RectangleComponent>(0, 255, 255, true);
}
