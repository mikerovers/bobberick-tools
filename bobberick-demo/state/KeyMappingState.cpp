#include "KeyMappingState.h"
#include <string>
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"

std::string KeyMappingState::getStateID() const
{
	return "keymapping";
}

void KeyMappingState::update()
{
	for (const auto& system : systems)
	{
		if (readyForExit)
			break;

		system->update();
	}
}

bool KeyMappingState::onEnter()
{
	makeTexts();

	return true;
}

bool KeyMappingState::onExit()
{
	return true;
}

bool KeyMappingState::shouldExit()
{
	return readyForExit;
}

void KeyMappingState::makeTexts()
{
	makeHeaders();
	makeKeyTexts();
	makeButtons();
}

void KeyMappingState::makeHeaders() const
{
	auto& headerText = entityManager.addEntity();
	headerText.addComponent<TransformComponent>(235, 50, 80, 450, 1);
	headerText.addComponent<TextComponent>("defaultLarge", "keyMappingText", "Key Mapping");
	entityManager.addEntityToGroup(headerText, getStateID());

	auto& movementHeader = entityManager.addEntity();
	movementHeader.addComponent<TransformComponent>(50, 150, 50, 250, 1);
	movementHeader.addComponent<TextComponent>("monoMedium", "movementText", "Movement:");
	entityManager.addEntityToGroup(movementHeader, getStateID());
	
	auto& fpsHeader = entityManager.addEntity();
	fpsHeader.addComponent<TransformComponent>(50, 425, 50, 250, 1);
	fpsHeader.addComponent<TextComponent>("monoMedium", "fpstText", "FPS Toggle:");
	entityManager.addEntityToGroup(fpsHeader, getStateID());
	
	auto& equipWeaponHeader = entityManager.addEntity();
	equipWeaponHeader.addComponent<TransformComponent>(550, 150, 50, 250, 1);
	equipWeaponHeader.addComponent<TextComponent>("monoMedium", "equipWeaponText", "Equip Weapon:");
	entityManager.addEntityToGroup(equipWeaponHeader, getStateID());
	
	auto& stopGameHeader = entityManager.addEntity();
	stopGameHeader.addComponent<TransformComponent>(550, 275, 50, 250, 1);
	stopGameHeader.addComponent<TextComponent>("monoMedium", "stopGameText", "Stop Game:");
	entityManager.addEntityToGroup(stopGameHeader, getStateID());
	
	auto& pauseGameHeader = entityManager.addEntity();
	pauseGameHeader.addComponent<TransformComponent>(550, 400, 50, 250, 1);
	pauseGameHeader.addComponent<TextComponent>("monoMedium", "pauseGameText", "Pause Game:");
	entityManager.addEntityToGroup(pauseGameHeader, getStateID());
}

void KeyMappingState::makeKeyTexts() const
{
	makeMovementKeysTexts();
	makeFPSKeysTexts();
	makeEquipWeaponKeysTexts();
	makeStopGameKeysTexts();
	makePauseGameKeysTexts();
}

void KeyMappingState::makeMovementKeysTexts() const
{
	/*
	 * Movement key set 1
	*/
	// Move left
	auto& moveLeftText1 = entityManager.addEntity();
	std::string moveLeftKey1 = "Move left 1: ";
	moveLeftText1.addComponent<TransformComponent>(50, 200, 17, 250, 1);
	moveLeftText1.addComponent<TextComponent>("monoSmall", "moveLeft1Text",
		moveLeftKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().left1)));
	entityManager.addEntityToGroup(moveLeftText1, getStateID());

	// Move right
	auto& moveRightText1 = entityManager.addEntity();
	std::string moveRightKey1 = "Move right 1: ";
	moveRightText1.addComponent<TransformComponent>(50, 225, 17, 250, 1);
	moveRightText1.addComponent<TextComponent>("monoSmall", "moveRight1Text",
		moveRightKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().right1)));
	entityManager.addEntityToGroup(moveRightText1, getStateID());

	// Move up
	auto& moveUpText1 = entityManager.addEntity();
	std::string moveUpKey1 = "Move up 1: ";
	moveUpText1.addComponent<TransformComponent>(50, 250, 17, 250, 1);
	moveUpText1.addComponent<TextComponent>("monoSmall", "moveUp1Text",
		moveUpKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().up1)));
	entityManager.addEntityToGroup(moveUpText1, getStateID());

	// Move down
	auto& moveDownText1 = entityManager.addEntity();
	std::string moveDownKey1 = "Move down 1: ";
	moveDownText1.addComponent<TransformComponent>(50, 275, 17, 250, 1);
	moveDownText1.addComponent<TextComponent>("monoSmall", "moveDown1Text",
		moveDownKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().down1)));
	entityManager.addEntityToGroup(moveDownText1, getStateID());

	/*
	 * Movement key set 2
	*/
	// Move left
	auto& moveLeftText2 = entityManager.addEntity();
	std::string moveLeftKey2 = "Move left 2: ";
	moveLeftText2.addComponent<TransformComponent>(50, 300, 17, 250, 1);
	moveLeftText2.addComponent<TextComponent>("monoSmall", "moveLeft2Text",
		moveLeftKey2.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().left2)));
	entityManager.addEntityToGroup(moveLeftText2, getStateID());

	// Move right
	auto& moveRightText2 = entityManager.addEntity();
	std::string moveRightKey2 = "Move right 2: ";
	moveRightText2.addComponent<TransformComponent>(50, 325, 17, 250, 1);
	moveRightText2.addComponent<TextComponent>("monoSmall", "moveRight2Text",
		moveRightKey2.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().right2)));
	entityManager.addEntityToGroup(moveRightText2, getStateID());

	// Move up
	auto& moveUpText2 = entityManager.addEntity();
	std::string moveUpKey2 = "Move up 2: ";
	moveUpText2.addComponent<TransformComponent>(50, 350, 17, 250, 1);
	moveUpText2.addComponent<TextComponent>("monoSmall", "moveUp2Text",
		moveUpKey2.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().up2)));
	entityManager.addEntityToGroup(moveUpText2, getStateID());

	// Move right
	auto& moveDownText2 = entityManager.addEntity();
	std::string moveDownKey2 = "Move down 2: ";
	moveDownText2.addComponent<TransformComponent>(50, 375, 17, 250, 1);
	moveDownText2.addComponent<TextComponent>("monoSmall", "moveDown2Text",
		moveDownKey2.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().down2)));
	entityManager.addEntityToGroup(moveDownText2, getStateID());
}

void KeyMappingState::makeFPSKeysTexts() const
{
	// FPS speed up
	auto& fpsUpText = entityManager.addEntity();
	std::string fpsUpKey = "FPS up: ";
	fpsUpText.addComponent<TransformComponent>(50, 475, 17, 200, 1);
	fpsUpText.addComponent<TextComponent>("monoSmall", "fpsUpText",
		fpsUpKey.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().fpsSpdUp)));
	entityManager.addEntityToGroup(fpsUpText, getStateID());

	// FPS speed down
	auto& fpsDownText = entityManager.addEntity();
	std::string fpsDownKey = "FPS down: ";
	fpsDownText.addComponent<TransformComponent>(50, 500, 17, 200, 1);
	fpsDownText.addComponent<TextComponent>("monoSmall", "fpsDownText",
		fpsDownKey.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().fpsSpdDown)));
	entityManager.addEntityToGroup(fpsDownText, getStateID());

	// FPS speed reset
	auto& fpsResetText = entityManager.addEntity();
	std::string fpsResetKey = "FPS reset: ";
	fpsResetText.addComponent<TransformComponent>(50, 525, 17, 200, 1);
	fpsResetText.addComponent<TextComponent>("monoSmall", "fpsResetText",
		fpsResetKey.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().fpsSpdReset)));
	entityManager.addEntityToGroup(fpsResetText, getStateID());

	// Show FPS
	// auto& fpsShowText = entityManager.addEntity();
	// std::string fpsShowKey = "Show FPS: ";
	// fpsShowText.addComponent<TransformComponent>(50, 550, 17, 200, 1);
	// fpsShowText.addComponent<TextComponent>("monoSmall", "fpsShowText",
	// 	fpsShowKey.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().fpsShow)));
	// entityManager.addEntityToGroup(fpsShowText, getStateID());
	
	// Hide FPS
	// auto& fpsHideText = entityManager.addEntity();
	// std::string fpsHideKey = "Hide FPS: ";
	// fpsHideText.addComponent<TransformComponent>(50, 575, 17, 200, 1);
	// fpsHideText.addComponent<TextComponent>("monoSmall", "fpsHideText",
	// 	fpsHideKey.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().fpsHide)));
	// entityManager.addEntityToGroup(fpsHideText, getStateID());
}

void KeyMappingState::makeEquipWeaponKeysTexts() const
{
	// Equip weapon key 1
	auto& equipWeaponText1 = entityManager.addEntity();
	std::string equipWeaponKey1 = "Equip weapon key 1: ";
	equipWeaponText1.addComponent<TransformComponent>(550, 200, 17, 300, 1);
	equipWeaponText1.addComponent<TextComponent>("monoSmall", "equipWeaponText1",
		equipWeaponKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().equipWeapon1)));
	entityManager.addEntityToGroup(equipWeaponText1, getStateID());

	// Equip weapon key 2
	auto& equipWeaponText2 = entityManager.addEntity();
	std::string equipWeaponKey2 = "Equip weapon key 2: ";
	equipWeaponText2.addComponent<TransformComponent>(550, 225, 17, 300, 1);
	equipWeaponText2.addComponent<TextComponent>("monoSmall", "equipWeaponText2",
		equipWeaponKey2.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().equipWeapon2)));
	entityManager.addEntityToGroup(equipWeaponText2, getStateID());
}

void KeyMappingState::makeStopGameKeysTexts() const
{
	// Stop game key 1
	auto& stopGameText1 = entityManager.addEntity();
	std::string stopGameKey1 = "Stop game key 1: ";
	stopGameText1.addComponent<TransformComponent>(550, 325, 17, 300, 1);
	stopGameText1.addComponent<TextComponent>("monoSmall", "stopGameText1",
		stopGameKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().stopGame1)));
	entityManager.addEntityToGroup(stopGameText1, getStateID());

	// Stop game key 2
	auto& stopGameText2 = entityManager.addEntity();
	std::string stopGameKey2 = "Stop game key 2: ";
	stopGameText2.addComponent<TransformComponent>(550, 350, 17, 300, 1);
	stopGameText2.addComponent<TextComponent>("monoSmall", "stopGameText2",
		stopGameKey2.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().stopGame2)));
	entityManager.addEntityToGroup(stopGameText2, getStateID());
}

void KeyMappingState::makePauseGameKeysTexts() const
{
	// Pause game key 1
	auto& pauseGameText1 = entityManager.addEntity();
	std::string pauseGameKey1 = "Pause game key 1: ";
	pauseGameText1.addComponent<TransformComponent>(550, 450, 17, 300, 1);
	pauseGameText1.addComponent<TextComponent>("monoSmall", "pauseGameText1",
		pauseGameKey1.append(ServiceManager::Instance()->getService<SettingsService>().getHumanReadableScancode(ServiceManager::Instance()->getService<SettingsService>().pauseGame1)));
	entityManager.addEntityToGroup(pauseGameText1, getStateID());
}

void KeyMappingState::makeButtons()
{
	auto& changeKeyButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto* changeKeyButtonComponent = new ButtonComponent([this]()
	{
		waitingForKeyPress = true;
		if (waitingForKeyPress)
		{
			while (waitingForKeyPress)
			{
				ServiceManager::Instance()->getService<SettingsService>().left1 = inputHandler.pollEventForKeyMapping();
				break;
			}
			waitingForKeyPress = false;
		}
	});
	
	changeKeyButton.addExistingComponent<ButtonComponent>(changeKeyButtonComponent);
	changeKeyButton.addComponent<TransformComponent>(400, 275, 64, 128, 1);
	changeKeyButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);
	
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(changeKeyButton, getStateID());







	auto& exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		readyForExit = true;
		ServiceManager::Instance()->getService<StateMachine>().popState();
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	exitButton.addComponent<TransformComponent>(410, 520, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());
}
