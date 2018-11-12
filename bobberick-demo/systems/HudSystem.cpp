#include "HudSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../components/PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include <string>

HudSystem::HudSystem(EntityManager &entityManager) : System(entityManager)
{
	
}

void HudSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>()) {
		PlayerStatsComponent& playerStats = entity->getComponent<PlayerStatsComponent>();

//		playerStats.xp += 99; // For testing purposes
//		playerStats.gold += 89; // For testing purposes
		playerStats.getHit(49, true); // For testing purposes

		playerStats.update();
		double healthWidth = ((double)playerStats.stats->getHP() / (double)playerStats.stats->getHPmax()) * barWidth;
		double shieldWidth = (playerStats.shdTime / playerStats.shdTimeMax) * barWidth;
		if (playerStats.shieldActive()) { // Bright blue bar if shield is currently active.
			shieldBox->getComponent<RectangleComponent>().red = 102;
			shieldBox->getComponent<RectangleComponent>().green = 255;
			shieldBox->getComponent<RectangleComponent>().blue = 255;
		} else if (playerStats.shdTime / playerStats.shdTimeMax < 0.5) { // Dark blue bar if shield is not yet ready to activate.
			shieldBox->getComponent<RectangleComponent>().red = 0;
			shieldBox->getComponent<RectangleComponent>().green = 51;
			shieldBox->getComponent<RectangleComponent>().blue = 153;
		} else { // Blue bar if shield is ready to activate.
			shieldBox->getComponent<RectangleComponent>().red = 0;
			shieldBox->getComponent<RectangleComponent>().green = 204;
			shieldBox->getComponent<RectangleComponent>().blue = 255;
		}

		//if (playerStats.shdTime == playerStats.shdTimeMax) { // For testing purposes
		//	playerStats.toggleShield();
		//}

		healthBox->getComponent<TransformComponent>().width = healthWidth;
		shieldBox->getComponent<TransformComponent>().width = shieldWidth;

		healthText->destroy();
		coinText->destroy();
		xpText->destroy();

		healthText = entityManager.addEntity();
		healthText->addComponent<TransformComponent>(20, 10, 30, 280, 1);
		healthText->addComponent<TextComponent>("assets/font/mono.ttf", "healthText", addSpaces(std::to_string(playerStats.stats->getHP()), 6, true) + " / " + addSpaces(std::to_string(playerStats.stats->getHPmax()), 6, false), 30);

		coinText = entityManager.addEntity();
		coinText->addComponent<TransformComponent>(barWidth + 67, 10, 30, 110, 1);
		coinText->addComponent<TextComponent>("assets/font/mono.ttf", "coinText", addSpaces(std::to_string(playerStats.gold), 6, false), 30);

		xpText = entityManager.addEntity();
		xpText->addComponent<TransformComponent>(barWidth + 227, 10, 30, 110, 1);
		xpText->addComponent<TextComponent>("assets/font/mono.ttf", "xpText", addSpaces(std::to_string(playerStats.xp), 6, false), 30);
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

	coinImage = entityManager.addEntity();
	coinImage->addComponent<TransformComponent>(barWidth + 17, 1, 48, 48, 1);
	coinImage->addComponent<SpriteComponent>("assets/image/gui/hud_gold.png", "coinImage", true);

	xpImage = entityManager.addEntity();
	xpImage->addComponent<TransformComponent>(barWidth + 177, 1, 48, 48, 1);
	xpImage->addComponent<SpriteComponent>("assets/image/gui/hud_xp.png", "xpImage", true);

	healthText = entityManager.addEntity();
	coinText = entityManager.addEntity();
	xpText = entityManager.addEntity();
}

std::string HudSystem::addSpaces(std::string string, const int goalChars, const bool leading) {
	std::string spaces = "";
	for (int i = string.length(); i < goalChars; i++) {
		spaces += " ";
	}
	if (leading) {
		return spaces + string;
	} else {
		return string + spaces;
	}
}
