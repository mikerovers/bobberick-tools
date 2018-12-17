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
	updateMovementKeysTexts();
	updateFPSKeysTexts();
	updateEquipWeaponKeysTexts();
	updateStopGameKeysTexts();
	updatePauseGameKeysTexts();
	updateShieldAndShootingKeysTexts();

	for (const auto& system : systems)
	{
		if (exiting)
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
	fpsHeader.addComponent<TransformComponent>(50, 425, 50, 100, 1);
	fpsHeader.addComponent<TextComponent>("monoMedium", "fpstText", "FPS:");
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
	
	auto& shootAndShieldHeader = entityManager.addEntity();
	shootAndShieldHeader.addComponent<TransformComponent>(550, 500, 50, 250, 1);
	shootAndShieldHeader.addComponent<TextComponent>("monoMedium", "shootAndShieldText", "Shoot & Shield:");
	entityManager.addEntityToGroup(shootAndShieldHeader, getStateID());
}

void KeyMappingState::makeKeyTexts() const
{
	makeMovementKeysTexts();
	makeFPSKeysTexts();
	makeEquipWeaponKeysTexts();
	makeStopGameKeysTexts();
	makePauseGameKeysTexts();
	makeShieldAndShootKeysTexts();
}

void KeyMappingState::makeMovementKeysTexts() const
{
	/*
	 * Movement key set 1
	*/
	// Move left
	// auto& moveLeftText1 = entityManager.addEntity();
	std::string moveLeftKey1 = "Move left 1: ";
	moveLeftText1.addComponent<TransformComponent>(50, 200, 17, 250, 1);
	moveLeftText1.addComponent<TextComponent>("monoSmall", "moveLeft1Text",
		moveLeftKey1.append(settings.getHumanReadableScancode(settings.left1)));
	entityManager.addEntityToGroup(moveLeftText1, getStateID());

	// Move right
	// auto& moveRightText1 = entityManager.addEntity();
	std::string moveRightKey1 = "Move right 1: ";
	moveRightText1.addComponent<TransformComponent>(50, 225, 17, 250, 1);
	moveRightText1.addComponent<TextComponent>("monoSmall", "moveRight1Text",
		moveRightKey1.append(settings.getHumanReadableScancode(settings.right1)));
	entityManager.addEntityToGroup(moveRightText1, getStateID());

	// Move up
	// auto& moveUpText1 = entityManager.addEntity();
	std::string moveUpKey1 = "Move up 1: ";
	moveUpText1.addComponent<TransformComponent>(50, 250, 17, 250, 1);
	moveUpText1.addComponent<TextComponent>("monoSmall", "moveUp1Text",
		moveUpKey1.append(settings.getHumanReadableScancode(settings.up1)));
	entityManager.addEntityToGroup(moveUpText1, getStateID());

	// Move down
	// auto& moveDownText1 = entityManager.addEntity();
	std::string moveDownKey1 = "Move down 1: ";
	moveDownText1.addComponent<TransformComponent>(50, 275, 17, 250, 1);
	moveDownText1.addComponent<TextComponent>("monoSmall", "moveDown1Text",
		moveDownKey1.append(settings.getHumanReadableScancode(settings.down1)));
	entityManager.addEntityToGroup(moveDownText1, getStateID());

	/*
	 * Movement key set 2
	*/
	// Move left
	// auto& moveLeftText2 = entityManager.addEntity();
	std::string moveLeftKey2 = "Move left 2: ";
	moveLeftText2.addComponent<TransformComponent>(50, 300, 17, 250, 1);
	moveLeftText2.addComponent<TextComponent>("monoSmall", "moveLeft2Text",
		moveLeftKey2.append(settings.getHumanReadableScancode(settings.left2)));
	entityManager.addEntityToGroup(moveLeftText2, getStateID());

	// Move right
	// auto& moveRightText2 = entityManager.addEntity();
	std::string moveRightKey2 = "Move right 2: ";
	moveRightText2.addComponent<TransformComponent>(50, 325, 17, 250, 1);
	moveRightText2.addComponent<TextComponent>("monoSmall", "moveRight2Text",
		moveRightKey2.append(settings.getHumanReadableScancode(settings.right2)));
	entityManager.addEntityToGroup(moveRightText2, getStateID());

	// Move up
	// auto& moveUpText2 = entityManager.addEntity();
	std::string moveUpKey2 = "Move up 2: ";
	moveUpText2.addComponent<TransformComponent>(50, 350, 17, 250, 1);
	moveUpText2.addComponent<TextComponent>("monoSmall", "moveUp2Text",
		moveUpKey2.append(settings.getHumanReadableScancode(settings.up2)));
	entityManager.addEntityToGroup(moveUpText2, getStateID());

	// Move right
	// auto& moveDownText2 = entityManager.addEntity();
	std::string moveDownKey2 = "Move down 2: ";
	moveDownText2.addComponent<TransformComponent>(50, 375, 17, 250, 1);
	moveDownText2.addComponent<TextComponent>("monoSmall", "moveDown2Text",
		moveDownKey2.append(settings.getHumanReadableScancode(settings.down2)));
	entityManager.addEntityToGroup(moveDownText2, getStateID());
}

void KeyMappingState::makeFPSKeysTexts() const
{
	// FPS speed up
	// auto& fpsUpText = entityManager.addEntity();
	std::string fpsUpKey = "FPS up: ";
	fpsUpText.addComponent<TransformComponent>(50, 475, 17, 200, 1);
	fpsUpText.addComponent<TextComponent>("monoSmall", "fpsUpText",
		fpsUpKey.append(settings.getHumanReadableScancode(settings.fpsSpdUp)));
	entityManager.addEntityToGroup(fpsUpText, getStateID());

	// FPS speed down
	// auto& fpsDownText = entityManager.addEntity();
	std::string fpsDownKey = "FPS down: ";
	fpsDownText.addComponent<TransformComponent>(50, 500, 17, 200, 1);
	fpsDownText.addComponent<TextComponent>("monoSmall", "fpsDownText",
		fpsDownKey.append(settings.getHumanReadableScancode(settings.fpsSpdDown)));
	entityManager.addEntityToGroup(fpsDownText, getStateID());

	// FPS speed reset
	// auto& fpsResetText = entityManager.addEntity();
	std::string fpsResetKey = "FPS reset: ";
	fpsResetText.addComponent<TransformComponent>(50, 525, 17, 200, 1);
	fpsResetText.addComponent<TextComponent>("monoSmall", "fpsResetText",
		fpsResetKey.append(settings.getHumanReadableScancode(settings.fpsSpdReset)));
	entityManager.addEntityToGroup(fpsResetText, getStateID());

	// Show FPS
	// auto& fpsShowText = entityManager.addEntity();
	std::string fpsShowKey = "Show FPS: ";
	fpsShowText.addComponent<TransformComponent>(50, 550, 17, 200, 1);
	fpsShowText.addComponent<TextComponent>("monoSmall", "fpsShowText",
		fpsShowKey.append(settings.getHumanReadableScancode(settings.fpsShow)));
	entityManager.addEntityToGroup(fpsShowText, getStateID());
	
	// Hide FPS
	// auto& fpsHideText = entityManager.addEntity();
	std::string fpsHideKey = "Hide FPS: ";
	fpsHideText.addComponent<TransformComponent>(50, 575, 17, 200, 1);
	fpsHideText.addComponent<TextComponent>("monoSmall", "fpsHideText",
		fpsHideKey.append(settings.getHumanReadableScancode(settings.fpsHide)));
	entityManager.addEntityToGroup(fpsHideText, getStateID());
}

void KeyMappingState::makeEquipWeaponKeysTexts() const
{
	// Equip weapon key 1
	// auto& equipWeaponText1 = entityManager.addEntity();
	std::string equipWeaponKey1 = "Equip weapon key 1: ";
	equipWeaponText1.addComponent<TransformComponent>(550, 200, 17, 300, 1);
	equipWeaponText1.addComponent<TextComponent>("monoSmall", "equipWeaponText1",
		equipWeaponKey1.append(settings.getHumanReadableScancode(settings.equipWeapon1)));
	entityManager.addEntityToGroup(equipWeaponText1, getStateID());

	// Equip weapon key 2
	// auto& equipWeaponText2 = entityManager.addEntity();
	std::string equipWeaponKey2 = "Equip weapon key 2: ";
	equipWeaponText2.addComponent<TransformComponent>(550, 225, 17, 300, 1);
	equipWeaponText2.addComponent<TextComponent>("monoSmall", "equipWeaponText2",
		equipWeaponKey2.append(settings.getHumanReadableScancode(settings.equipWeapon2)));
	entityManager.addEntityToGroup(equipWeaponText2, getStateID());
}

void KeyMappingState::makeStopGameKeysTexts() const
{
	// Stop game key 1
	// auto& stopGameText1 = entityManager.addEntity();
	std::string stopGameKey1 = "Stop game key 1: ";
	stopGameText1.addComponent<TransformComponent>(550, 325, 17, 300, 1);
	stopGameText1.addComponent<TextComponent>("monoSmall", "stopGameText1",
		stopGameKey1.append(settings.getHumanReadableScancode(settings.stopGame1)));
	entityManager.addEntityToGroup(stopGameText1, getStateID());

	// Stop game key 2
	// auto& stopGameText2 = entityManager.addEntity();
	std::string stopGameKey2 = "Stop game key 2: ";
	stopGameText2.addComponent<TransformComponent>(550, 350, 17, 300, 1);
	stopGameText2.addComponent<TextComponent>("monoSmall", "stopGameText2",
		stopGameKey2.append(settings.getHumanReadableScancode(settings.stopGame2)));
	entityManager.addEntityToGroup(stopGameText2, getStateID());
}

void KeyMappingState::makePauseGameKeysTexts() const
{
	// Pause game key 1
	// auto& pauseGameText1 = entityManager.addEntity();
	std::string pauseGameKey1 = "Pause game key 1: ";
	pauseGameText1.addComponent<TransformComponent>(550, 450, 17, 300, 1);
	pauseGameText1.addComponent<TextComponent>("monoSmall", "pauseGameText1",
		pauseGameKey1.append(settings.getHumanReadableScancode(settings.pauseGame1)));
	entityManager.addEntityToGroup(pauseGameText1, getStateID());
}

void KeyMappingState::makeShieldAndShootKeysTexts() const
{
	std::string activateShieldKey = "Activate shield: ";
	activateShieldText.addComponent<TransformComponent>(550, 550, 17, 300, 1);
	activateShieldText.addComponent<TextComponent>("monoSmall", "activateShieldText",
		activateShieldKey.append(settings.getHumanReadableScancode(settings.activateShield)));
	entityManager.addEntityToGroup(activateShieldText, getStateID());

	// TODO: Add shooting to the key binding
	// std::string shootNormalKey = "Shoot normal: ";
	// shootNormalText.addComponent<TransformComponent>(550, 575, 17, 300, 1);
	// shootNormalText.addComponent<TextComponent>("monoSmall", "shootNormalText",
	// 	shootNormalKey.append(settings.getHumanReadableScancode(settings.shootNormal)));
	// entityManager.addEntityToGroup(shootNormalText, getStateID());

	// TODO: Add shooting to the key binding
	// std::string shootMagicKey = "Shoot magic: ";
	// shootMagicText.addComponent<TransformComponent>(550, 600, 17, 300, 1);
	// shootMagicText.addComponent<TextComponent>("monoSmall", "shootMagicText",
	// 	shootMagicKey.append(settings.getHumanReadableScancode(settings.shootMagic)));
	// entityManager.addEntityToGroup(shootMagicText, getStateID());
}

void KeyMappingState::makeButtons()
{
	makeChangeMovementKeyButtons();
	makeChangeFPSKeyButtons();
	makeChangeEquipWeaponKeyButtons();
	makeChangeStopGameKeyButtons();
	makeChangePauseKeyButtons();
	makeChangeShieldAndShootingKeyButtons();
	makeExitButton();
}

void KeyMappingState::makeChangeMovementKeyButtons()
{
	auto& left1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* left1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.left1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.left1;
	});

	left1Button.addExistingComponent<ButtonComponent>(left1ButtonComponent);
	left1Button.addComponent<TransformComponent>(310, 193, 22, 44, 1);
	left1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(left1Button, getStateID());

	auto& right1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* right1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.right1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.right1;
	});

	right1Button.addExistingComponent<ButtonComponent>(right1ButtonComponent);
	right1Button.addComponent<TransformComponent>(310, 218, 22, 44, 1);
	right1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(right1Button, getStateID());

	auto& up1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* up1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.up1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.up1;
	});

	up1Button.addExistingComponent<ButtonComponent>(up1ButtonComponent);
	up1Button.addComponent<TransformComponent>(310, 243, 22, 44, 1);
	up1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(up1Button, getStateID());

	auto& down1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* down1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.down1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.down1;
	});

	down1Button.addExistingComponent<ButtonComponent>(down1ButtonComponent);
	down1Button.addComponent<TransformComponent>(310, 268, 22, 44, 1);
	down1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(down1Button, getStateID());

	auto& left2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* left2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.left2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.left2;
	});

	left2Button.addExistingComponent<ButtonComponent>(left2ButtonComponent);
	left2Button.addComponent<TransformComponent>(310, 293, 22, 44, 1);
	left2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(left2Button, getStateID());

	auto& right2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* right2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.right2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.right2;
	});

	right2Button.addExistingComponent<ButtonComponent>(right2ButtonComponent);
	right2Button.addComponent<TransformComponent>(310, 318, 22, 44, 1);
	right2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(right2Button, getStateID());

	auto& up2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* up2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.up2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.up2;
	});

	up2Button.addExistingComponent<ButtonComponent>(up2ButtonComponent);
	up2Button.addComponent<TransformComponent>(310, 343, 22, 44, 1);
	up2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(up2Button, getStateID());

	auto& down2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* down2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.down2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.down2;
	});

	down2Button.addExistingComponent<ButtonComponent>(down2ButtonComponent);
	down2Button.addComponent<TransformComponent>(310, 368, 22, 44, 1);
	down2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(down2Button, getStateID());
}

void KeyMappingState::makeChangeFPSKeyButtons()
{
	auto& fpsSpdUpButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsSpdUpButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsSpdUp;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsSpdUp;
	});

	fpsSpdUpButton.addExistingComponent<ButtonComponent>(fpsSpdUpButtonComponent);
	fpsSpdUpButton.addComponent<TransformComponent>(260, 468, 22, 44, 1);
	fpsSpdUpButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsSpdUpButton, getStateID());

	auto& fpsSpdDownButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsSpdDownButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsSpdDown;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsSpdDown;
	});

	fpsSpdDownButton.addExistingComponent<ButtonComponent>(fpsSpdDownButtonComponent);
	fpsSpdDownButton.addComponent<TransformComponent>(260, 493, 22, 44, 1);
	fpsSpdDownButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsSpdDownButton, getStateID());

	auto& fpsResetButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsResetButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsSpdReset;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsSpdReset;
	});

	fpsResetButton.addExistingComponent<ButtonComponent>(fpsResetButtonComponent);
	fpsResetButton.addComponent<TransformComponent>(260, 518, 22, 44, 1);
	fpsResetButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsResetButton, getStateID());

	auto& fpsShowButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsShowButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsShow;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsShow;
	});

	fpsShowButton.addExistingComponent<ButtonComponent>(fpsShowButtonComponent);
	fpsShowButton.addComponent<TransformComponent>(260, 543, 22, 44, 1);
	fpsShowButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsShowButton, getStateID());

	auto& fpsHideButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsHideButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsHide;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsHide;
	});

	fpsHideButton.addExistingComponent<ButtonComponent>(fpsHideButtonComponent);
	fpsHideButton.addComponent<TransformComponent>(260, 568, 22, 44, 1);
	fpsHideButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsHideButton, getStateID());
}

void KeyMappingState::makeChangeEquipWeaponKeyButtons()
{
	auto& equipWeapon1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* equipWeapon1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.equipWeapon1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.equipWeapon1;
	});

	equipWeapon1Button.addExistingComponent<ButtonComponent>(equipWeapon1ButtonComponent);
	equipWeapon1Button.addComponent<TransformComponent>(860, 193, 22, 44, 1);
	equipWeapon1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(equipWeapon1Button, getStateID());

	auto& equipWeapon2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* equipWeapon2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.equipWeapon2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.equipWeapon2;
	});

	equipWeapon2Button.addExistingComponent<ButtonComponent>(equipWeapon2ButtonComponent);
	equipWeapon2Button.addComponent<TransformComponent>(860, 218, 22, 44, 1);
	equipWeapon2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(equipWeapon2Button, getStateID());
}

void KeyMappingState::makeChangeStopGameKeyButtons()
{
	auto& stopGame1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* stopGame1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.stopGame1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.stopGame1;
	});

	stopGame1Button.addExistingComponent<ButtonComponent>(stopGame1ButtonComponent);
	stopGame1Button.addComponent<TransformComponent>(860, 318, 22, 44, 1);
	stopGame1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(stopGame1Button, getStateID());

	auto& stopGame2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* stopGame2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.stopGame2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.stopGame2;
	});

	stopGame2Button.addExistingComponent<ButtonComponent>(stopGame2ButtonComponent);
	stopGame2Button.addComponent<TransformComponent>(860, 343, 22, 44, 1);
	stopGame2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(stopGame2Button, getStateID());
}

void KeyMappingState::makeChangePauseKeyButtons()
{
	auto& pauseGame1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* pauseGame1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.pauseGame1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.pauseGame1;
	});

	pauseGame1Button.addExistingComponent<ButtonComponent>(pauseGame1ButtonComponent);
	pauseGame1Button.addComponent<TransformComponent>(860, 443, 22, 44, 1);
	pauseGame1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(pauseGame1Button, getStateID());
}

void KeyMappingState::makeChangeShieldAndShootingKeyButtons()
{
	auto& activateShieldButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* activateShieldButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.activateShield;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.activateShield;
	});

	activateShieldButton.addExistingComponent<ButtonComponent>(activateShieldButtonComponent);
	activateShieldButton.addComponent<TransformComponent>(860, 543, 22, 44, 1);
	activateShieldButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(activateShieldButton, getStateID());

	// TODO: Add shooting to the key binding
	// auto& shootNormalButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	//
	// auto* shootNormalButtonComponent = new ButtonComponent([this]()
	// {
	// 	inputHandler.newKey = settings.shootNormal;
	// 	inputHandler.isMappingKey(true);
	// 	settings.keyToChange = settings.shootNormal;
	//
	// 	// save.keep("shootNormal", settings.shootNormal);
	// });
	//
	// shootNormalButton.addExistingComponent<ButtonComponent>(shootNormalButtonComponent);
	// shootNormalButton.addComponent<TransformComponent>(860, 568, 22, 44, 1);
	// shootNormalButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);
	//
	// ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(shootNormalButton, getStateID());

	// TODO: Add shooting to the key binding
	// auto& shootMagicButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	//
	// auto* shootMagicButtonComponent = new ButtonComponent([this]()
	// {
	// 	inputHandler.newKey = settings.shootMagic;
	// 	inputHandler.isMappingKey(true);
	// 	settings.keyToChange = settings.shootMagic;
	//
	// 	// save.keep("shootMagic", settings.shootMagic);
	// });
	//
	// shootMagicButton.addExistingComponent<ButtonComponent>(shootMagicButtonComponent);
	// shootMagicButton.addComponent<TransformComponent>(860, 593, 22, 44, 1);
	// shootMagicButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);
	//
	// ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(shootMagicButton, getStateID());
}

void KeyMappingState::makeExitButton()
{
	auto& exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		readyForExit = true;
		ServiceManager::Instance()->getService<StateMachine>().popState();
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	exitButton.addComponent<TransformComponent>(settings.gameWidth - 138, 10, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());
}

void KeyMappingState::updateMovementKeysTexts() const
{
	std::string updatedText = "Move left 1: ";
	moveLeftText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.left1)));

	updatedText = "Move right 1: ";
	moveRightText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.right1)));

	updatedText = "Move up 1: ";
	moveUpText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.up1)));

	updatedText = "Move down 1: ";
	moveDownText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.down1)));

	updatedText = "Move left 2: ";
	moveLeftText2.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.left2)));

	updatedText = "Move right 2: ";
	moveRightText2.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.right2)));

	updatedText = "Move up 2: ";
	moveUpText2.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.up2)));

	updatedText = "Move down 2: ";
	moveDownText2.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.down2)));
}

void KeyMappingState::updateFPSKeysTexts() const
{
	std::string updatedText = "FPS up: ";
	fpsUpText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.fpsSpdUp)));

	updatedText = "FPS down: ";
	fpsDownText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.fpsSpdDown)));

	updatedText = "FPS reset: ";
	fpsResetText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.fpsSpdReset)));

	updatedText = "Show FPS: ";
	fpsShowText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.fpsShow)));

	updatedText = "Hide FPS: ";
	fpsHideText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.fpsHide)));
}

void KeyMappingState::updateEquipWeaponKeysTexts() const
{
	std::string updatedText = "Equip weapon key 1: ";
	equipWeaponText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.equipWeapon1)));

	updatedText = "Equip weapon key 2: ";
	equipWeaponText2.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.equipWeapon2)));
}

void KeyMappingState::updateStopGameKeysTexts() const
{
	std::string updatedText = "Stop game key 1: ";
	stopGameText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.stopGame1)));

	updatedText = "Stop game key 2: ";
	stopGameText2.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.stopGame2)));
}

void KeyMappingState::updatePauseGameKeysTexts() const
{
	std::string updatedText = "Pause game key 1: ";
	pauseGameText1.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.pauseGame1)));
}

void KeyMappingState::updateShieldAndShootingKeysTexts() const
{
	std::string updatedText = "Activate shield: ";
	activateShieldText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.activateShield)));

	// TODO: Add shooting to the key binding
	// updatedText = "Shoot normal: ";
	// shootNormalText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.shootNormal)));

	// TODO: Add shooting to the key binding
	// updatedText = "Shoot magic: ";
	// shootMagicText.getComponent<TextComponent>().setText(updatedText.append(settings.getHumanReadableScancode(settings.shootMagic)));
}
