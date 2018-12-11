#include "HudSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../services/PlayerStatsService.h"
#include "../components/PlayerComponent.h"
#include "../components/InventoryComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-framework/src/services/FrameHandler.h"
#include "../../bobberick-framework/src/util/TextFormatter.h"
#include <string>
#include "../components/InventorySlotComponent.h"

HudSystem::HudSystem(EntityManager& entityManager) : System(entityManager),
                                                     hudBox(entityManager.addEntity()),
													 compareBox(entityManager.addEntity()),
                                                     outerBox(entityManager.addEntity()),
                                                     innerBox(entityManager.addEntity()),
                                                     healthBox(entityManager.addEntity()),
                                                     shieldBox(entityManager.addEntity()),
                                                     healthText(entityManager.addEntity()),
                                                     coinImage(entityManager.addEntity()),
                                                     coinText(entityManager.addEntity()),
                                                     xpImage(entityManager.addEntity()),
                                                     xpText(entityManager.addEntity()),
													 oldWeaponName(entityManager.addEntity()),
													 oldWeaponText(entityManager.addEntity()),
													 newWeaponText(entityManager.addEntity()),
													 newWeaponName(entityManager.addEntity()),
                                                     inventory(entityManager.addEntity()),
                                                     inventorySlot1(entityManager.addEntity()),
                                                     inventorySlot2(entityManager.addEntity()),
                                                     fpsCounter(entityManager.addEntity())
{
}

void HudSystem::update()
{
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	const bool fpsOn = ServiceManager::Instance()->getService<SettingsService>().fps;

	fpsMiddlerCount++;
	auto fps = ServiceManager::Instance()->getService<FrameHandler>().getCurrentFps();
	fpsMiddlerVector.push_back(fps);

	if (fpsMiddlerCount == fpsMiddlerDivideBy) {

		int fpsCount = 0;
		for (auto &countedFps : fpsMiddlerVector)
		{
			fpsCount += countedFps;
		}

		fpsMiddlerResult = fpsCount / fpsMiddlerDivideBy;
		fpsMiddlerCount = 0;
		fpsMiddlerVector.clear();
	}
	


	playerStats.update();
	const auto healthWidth = static_cast<double>(playerStats.getHP()) / static_cast<double>(playerStats.getHPmax()) * barWidth;
	const auto shieldWidth = static_cast<double>(playerStats.getSHD()) / static_cast<double>(playerStats.getSHDmax()) * barWidth;
	if (playerStats.getSHDactive())
	{
		// Bright blue bar if shield is currently active.
		shieldBox.getComponent<RectangleComponent>().red = 153;
		shieldBox.getComponent<RectangleComponent>().green = 255;
		shieldBox.getComponent<RectangleComponent>().blue = 255;
	}
	else if (playerStats.getSHD() / playerStats.getSHDmax() < 0.5)
	{
		// Dark blue bar if shield is not yet ready to activate.
		shieldBox.getComponent<RectangleComponent>().red = 0;
		shieldBox.getComponent<RectangleComponent>().green = 51;
		shieldBox.getComponent<RectangleComponent>().blue = 153;
	}
	else
	{
		// Blue bar if shield is ready to activate.
		shieldBox.getComponent<RectangleComponent>().red = 0;
		shieldBox.getComponent<RectangleComponent>().green = 204;
		shieldBox.getComponent<RectangleComponent>().blue = 255;
	}
	inventorySlot1.getComponent<SpriteComponent>().setTexture(playerStats.normalWeapon.textureID.c_str());
	inventorySlot2.getComponent<SpriteComponent>().setTexture(playerStats.magicWeapon.textureID.c_str());

	healthBox.getComponent<TransformComponent>().width = healthWidth;
	shieldBox.getComponent<TransformComponent>().width = shieldWidth;

	TextFormatter textFormatter = TextFormatter{};
	healthText.getComponent<TextComponent>().setText(
		textFormatter.addSpaces(std::to_string(playerStats.getHP()), 6, true) + " / " + TextFormatter{}.addSpaces(
			std::to_string(playerStats.getHPmax()), 6, false));
	coinText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.gold), 6, false));
	xpText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.xp), 6, false));

	if (fpsCounter.hasComponent<TextComponent>()) {
		if (fpsOn) {
				fpsCounter.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(fpsMiddlerResult), 3, true));
			}
		else {
			fpsCounter.getComponent<TextComponent>().setText(" ");
		}
	}

	if (!comparing && playerStats.compareTime > 0) {
		if (playerStats.comparingWeapon.isMagic) {
			startCompare(playerStats.magicWeapon, playerStats.comparingWeapon);
		} else {
			startCompare(playerStats.normalWeapon, playerStats.comparingWeapon);
		}
	} else if (comparing && playerStats.compareTime <= 0) {
		stopCompare();
	}
}

void HudSystem::init()
{
	const int gameWidth = ServiceManager::Instance()->getService<SettingsService>().gameWidth;
	const int gameHeight = ServiceManager::Instance()->getService<SettingsService>().gameHeight;
	TextFormatter textFormatter = TextFormatter{};

	hudBox.addComponent<TransformComponent>(0, 0, 50, gameWidth, 1);
	hudBox.addComponent<RectangleComponent>(51, 51, 204, true);

	compareBox.addComponent<TransformComponent>(barWidth + 845, 50, 40, gameWidth - (barWidth + 345), 1); // Start off-screen.
	compareBox.addComponent<RectangleComponent>(51, 51, 204, true);

	outerBox.addComponent<TransformComponent>(9, 9, 32, barWidth + 2, 1);
	outerBox.addComponent<RectangleComponent>(0, 0, 0, false);

	innerBox.addComponent<TransformComponent>(10, 10, 30, barWidth, 1);
	innerBox.addComponent<RectangleComponent>(128, 128, 128, true);

	healthBox.addComponent<TransformComponent>(10, 10, 30, barWidth, 1);
	healthBox.addComponent<RectangleComponent>(255, 0, 0, true);

	shieldBox.addComponent<TransformComponent>(10, 35, 5, barWidth, 1);
	shieldBox.addComponent<RectangleComponent>(0, 255, 255, true);

	coinImage.addComponent<TransformComponent>(barWidth + 17, 1, 48, 48, 1);
	coinImage.addComponent<SpriteComponent>("hudGold", 1);

	xpImage.addComponent<TransformComponent>(barWidth + 177, 1, 48, 48, 1);
	xpImage.addComponent<SpriteComponent>("hudXp", 1);

	healthText.addComponent<TransformComponent>(20, 10, 30, 280, 1);
	healthText.addComponent<TextComponent>("monoMedium", "healthText", " ");

	coinText.addComponent<TransformComponent>(barWidth + 67, 10, 30, 110, 1);
	coinText.addComponent<TextComponent>("monoMedium", "coinText", " ");

	xpText.addComponent<TransformComponent>(barWidth + 227, 10, 30, 110, 1);
	xpText.addComponent<TextComponent>("monoMedium", "xpText", " ");

	oldWeaponName.addComponent<TransformComponent>(barWidth + 350, 7, 20, 300, 1);
	oldWeaponName.addComponent<TextComponent>("monoSmall", "oldWeaponName", " ");

	oldWeaponText.addComponent<TransformComponent>(barWidth + 350, 27, 20, 300, 1);
	oldWeaponText.addComponent<TextComponent>("monoSmall", "oldWeaponText", " ");

	newWeaponName.addComponent<TransformComponent>(barWidth + 350, 47, 20, 300, 1);
	newWeaponName.addComponent<TextComponent>("monoSmall", "newWeaponName", " ");

	newWeaponText.addComponent<TransformComponent>(barWidth + 350, 67, 20, 300, 1);
	newWeaponText.addComponent<TextComponent>("monoSmall", "newWeaponText", " ");

	inventory.addComponent<TransformComponent>(10, gameHeight - 60, 60, 130, 1);
	inventory.addComponent<RectangleComponent>(161, 64, 5, true);

	inventorySlot1.addComponent<TransformComponent>(20, gameHeight - 55, 50, 50, 1);
	inventorySlot1.addComponent<RectangleComponent>(212, 154, 44, true);
	inventorySlot1.addComponent<InventorySlotComponent>("");
	inventorySlot1.addComponent<SpriteComponent>("", 1);

	inventorySlot2.addComponent<TransformComponent>(80, gameHeight - 55, 50, 50, 1);
	inventorySlot2.addComponent<RectangleComponent>(212, 154, 44, true);
	inventorySlot2.addComponent<InventorySlotComponent>("");
	inventorySlot2.addComponent<SpriteComponent>("", 1);
	inventorySlot1.addComponent<InventorySlotComponent>("normal");

	inventorySlot2.addComponent<TransformComponent>(80, gameHeight - 55, 50, 50, 1);
	inventorySlot2.addComponent<RectangleComponent>(212, 154, 44, true);
	inventorySlot2.addComponent<InventorySlotComponent>("magic");

	fpsCounter.addComponent<TransformComponent>(gameWidth - 60, 10, 30, 52, 1);
	fpsCounter.addComponent<TextComponent>("monoMedium", "fps", " ");

	auto players = ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<
		PlayerComponent>();
	for (auto player : players)
	{
		for (const auto& group : player->getGroups())
		{
			auto& serviceManager = ServiceManager::Instance()->getService<EntityManager>();
			serviceManager.addEntityToGroup(hudBox, group);
			serviceManager.addEntityToGroup(compareBox, group);
			serviceManager.addEntityToGroup(outerBox, group);
			serviceManager.addEntityToGroup(innerBox, group);
			serviceManager.addEntityToGroup(healthBox, group);
			serviceManager.addEntityToGroup(shieldBox, group);
			serviceManager.addEntityToGroup(coinImage, group);
			serviceManager.addEntityToGroup(xpImage, group);
			serviceManager.addEntityToGroup(healthText, group);
			serviceManager.addEntityToGroup(coinText, group);
			serviceManager.addEntityToGroup(xpText, group);
			serviceManager.addEntityToGroup(oldWeaponName, group);
			serviceManager.addEntityToGroup(oldWeaponText, group);
			serviceManager.addEntityToGroup(newWeaponName, group);
			serviceManager.addEntityToGroup(newWeaponText, group);
			serviceManager.addEntityToGroup(inventory, group);
			serviceManager.addEntityToGroup(inventorySlot1, group);
			serviceManager.addEntityToGroup(inventorySlot2, group);
			serviceManager.addEntityToGroup(fpsCounter, group);
		}
	}
}

void HudSystem::startCompare(WeaponComponent oldWeapon, WeaponComponent newWeapon) {
	TextFormatter textFormatter = TextFormatter();
	comparing = true;
	
	compareBox.getComponent<TransformComponent>().position.x -= 500; // Get on to the screen
	oldWeaponName.getComponent<TextComponent>().setText(textFormatter.addSpaces(oldWeapon.name, 35, false));
	oldWeaponText.getComponent<TextComponent>().setText(textFormatter.addSpaces("Old weapon: Power " + std::to_string(oldWeapon.power) + ", Delay " + std::to_string(oldWeapon.fireDelay), 35, false));
	newWeaponName.getComponent<TextComponent>().setText(textFormatter.addSpaces(newWeapon.name, 35, false));
	newWeaponText.getComponent<TextComponent>().setText(textFormatter.addSpaces("New weapon: Power " + std::to_string(newWeapon.power) + ", Delay " + std::to_string(newWeapon.fireDelay), 35, false));
}

void HudSystem::stopCompare() {
	comparing = false;
	
	compareBox.getComponent<TransformComponent>().position.x += 500; // Go off the screen
	oldWeaponName.getComponent<TextComponent>().setText(" ");
	oldWeaponText.getComponent<TextComponent>().setText(" ");
	newWeaponName.getComponent<TextComponent>().setText(" ");
	newWeaponText.getComponent<TextComponent>().setText(" ");
}