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
	updatePauseGameKeysTexts();
	updateShieldAndShootingKeysTexts();
	updateChangingKeyText();

	for (const auto& system : systems)
	{
		if (exiting)
			break;

		system->update();
	}
}

bool KeyMappingState::onEnter()
{
	changingKeyText.addComponent<TransformComponent>(350, 140, 17, 275, 1);
	changingKeyText.addComponent<TextComponent>("monoSmall", "changingKeyText", changingKeyString);

	makeBackground();
	makeTexts();
	makeButtons();

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

void KeyMappingState::makeBackground() const
{
	auto& background = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	background.addComponent<TransformComponent>(0, 0, 704, 960, 1);
	background.addComponent<SpriteComponent>("menuBackground", 0);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(background, getStateID());
}

void KeyMappingState::makeTexts()
{
	makeHeaders();
	makeKeyTexts();
}

void KeyMappingState::makeHeaders() const
{
	auto& headerText = entityManager.addEntity();
	headerText.addComponent<TransformComponent>(255, 50, 80, 450, 1);
	headerText.addComponent<TextComponent>("defaultLarge", "keyMappingHeader", "Key Mapping");
	entityManager.addEntityToGroup(headerText, getStateID());

	auto& movementHeader = entityManager.addEntity();
	movementHeader.addComponent<TransformComponent>(100, 175, 50, 250, 1);
	movementHeader.addComponent<TextComponent>("monoMedium", "movementText", "Movement:");
	entityManager.addEntityToGroup(movementHeader, getStateID());
	
	auto& fpsHeader = entityManager.addEntity();
	fpsHeader.addComponent<TransformComponent>(100, 450, 50, 100, 1);
	fpsHeader.addComponent<TextComponent>("monoMedium", "fpstText", "FPS:");
	entityManager.addEntityToGroup(fpsHeader, getStateID());
	
	auto& equipWeaponHeader = entityManager.addEntity();
	equipWeaponHeader.addComponent<TransformComponent>(500, 175, 50, 250, 1);
	equipWeaponHeader.addComponent<TextComponent>("monoMedium", "equipWeaponText", "Equip Weapon:");
	entityManager.addEntityToGroup(equipWeaponHeader, getStateID());
	
	auto& pauseGameHeader = entityManager.addEntity();
	pauseGameHeader.addComponent<TransformComponent>(500, 275, 50, 250, 1);
	pauseGameHeader.addComponent<TextComponent>("monoMedium", "pauseGameText", "Pause Game:");
	entityManager.addEntityToGroup(pauseGameHeader, getStateID());
	
	auto& shootAndShieldHeader = entityManager.addEntity();
	shootAndShieldHeader.addComponent<TransformComponent>(500, 375, 50, 250, 1);
	shootAndShieldHeader.addComponent<TextComponent>("monoMedium", "shootAndShieldText", "Shield:");
	entityManager.addEntityToGroup(shootAndShieldHeader, getStateID());
}

void KeyMappingState::makeKeyTexts() const
{
	makeMovementKeysTexts();
	makeFPSKeysTexts();
	makeEquipWeaponKeysTexts();
	makePauseGameKeysTexts();
	makeShieldAndShootKeysTexts();
}

void KeyMappingState::makeMovementKeysTexts() const
{
	/*
	 * Movement key set 1
	*/
	// Move left
	std::string moveLeftKey1 = "Move left 1: ";
	moveLeftText1.addComponent<TransformComponent>(100, 225, 17, 250, 1);
	moveLeftText1.addComponent<TextComponent>("monoSmall", "moveLeft1Text",
		moveLeftKey1.append(settings.getHumanReadableScancode(settings.left1)));
	entityManager.addEntityToGroup(moveLeftText1, getStateID());

	// Move right
	std::string moveRightKey1 = "Move right 1: ";
	moveRightText1.addComponent<TransformComponent>(100, 250, 17, 250, 1);
	moveRightText1.addComponent<TextComponent>("monoSmall", "moveRight1Text",
		moveRightKey1.append(settings.getHumanReadableScancode(settings.right1)));
	entityManager.addEntityToGroup(moveRightText1, getStateID());

	// Move up
	std::string moveUpKey1 = "Move up 1: ";
	moveUpText1.addComponent<TransformComponent>(100, 275, 17, 250, 1);
	moveUpText1.addComponent<TextComponent>("monoSmall", "moveUp1Text",
		moveUpKey1.append(settings.getHumanReadableScancode(settings.up1)));
	entityManager.addEntityToGroup(moveUpText1, getStateID());

	// Move down
	std::string moveDownKey1 = "Move down 1: ";
	moveDownText1.addComponent<TransformComponent>(100, 300, 17, 250, 1);
	moveDownText1.addComponent<TextComponent>("monoSmall", "moveDown1Text",
		moveDownKey1.append(settings.getHumanReadableScancode(settings.down1)));
	entityManager.addEntityToGroup(moveDownText1, getStateID());

	/*
	 * Movement key set 2
	*/
	// Move left
	std::string moveLeftKey2 = "Move left 2: ";
	moveLeftText2.addComponent<TransformComponent>(100, 325, 17, 250, 1);
	moveLeftText2.addComponent<TextComponent>("monoSmall", "moveLeft2Text",
		moveLeftKey2.append(settings.getHumanReadableScancode(settings.left2)));
	entityManager.addEntityToGroup(moveLeftText2, getStateID());

	// Move right
	std::string moveRightKey2 = "Move right 2: ";
	moveRightText2.addComponent<TransformComponent>(100, 350, 17, 250, 1);
	moveRightText2.addComponent<TextComponent>("monoSmall", "moveRight2Text",
		moveRightKey2.append(settings.getHumanReadableScancode(settings.right2)));
	entityManager.addEntityToGroup(moveRightText2, getStateID());

	// Move up
	std::string moveUpKey2 = "Move up 2: ";
	moveUpText2.addComponent<TransformComponent>(100, 375, 17, 250, 1);
	moveUpText2.addComponent<TextComponent>("monoSmall", "moveUp2Text",
		moveUpKey2.append(settings.getHumanReadableScancode(settings.up2)));
	entityManager.addEntityToGroup(moveUpText2, getStateID());

	// Move right
	std::string moveDownKey2 = "Move down 2: ";
	moveDownText2.addComponent<TransformComponent>(100, 400, 17, 250, 1);
	moveDownText2.addComponent<TextComponent>("monoSmall", "moveDown2Text",
		moveDownKey2.append(settings.getHumanReadableScancode(settings.down2)));
	entityManager.addEntityToGroup(moveDownText2, getStateID());
}

void KeyMappingState::makeFPSKeysTexts() const
{
	// FPS speed up
	std::string fpsUpKey = "FPS up: ";
	fpsUpText.addComponent<TransformComponent>(100, 500, 17, 200, 1);
	fpsUpText.addComponent<TextComponent>("monoSmall", "fpsUpText",
		fpsUpKey.append(settings.getHumanReadableScancode(settings.fpsSpdUp)));
	entityManager.addEntityToGroup(fpsUpText, getStateID());

	// FPS speed down
	std::string fpsDownKey = "FPS down: ";
	fpsDownText.addComponent<TransformComponent>(100, 525, 17, 200, 1);
	fpsDownText.addComponent<TextComponent>("monoSmall", "fpsDownText",
		fpsDownKey.append(settings.getHumanReadableScancode(settings.fpsSpdDown)));
	entityManager.addEntityToGroup(fpsDownText, getStateID());

	// FPS speed reset
	std::string fpsResetKey = "FPS reset: ";
	fpsResetText.addComponent<TransformComponent>(100, 550, 17, 200, 1);
	fpsResetText.addComponent<TextComponent>("monoSmall", "fpsResetText",
		fpsResetKey.append(settings.getHumanReadableScancode(settings.fpsSpdReset)));
	entityManager.addEntityToGroup(fpsResetText, getStateID());

	// Show FPS
	std::string fpsShowKey = "Show FPS: ";
	fpsShowText.addComponent<TransformComponent>(100, 575, 17, 200, 1);
	fpsShowText.addComponent<TextComponent>("monoSmall", "fpsShowText",
		fpsShowKey.append(settings.getHumanReadableScancode(settings.fpsShow)));
	entityManager.addEntityToGroup(fpsShowText, getStateID());
	
	// Hide FPS
	std::string fpsHideKey = "Hide FPS: ";
	fpsHideText.addComponent<TransformComponent>(100, 600, 17, 200, 1);
	fpsHideText.addComponent<TextComponent>("monoSmall", "fpsHideText",
		fpsHideKey.append(settings.getHumanReadableScancode(settings.fpsHide)));
	entityManager.addEntityToGroup(fpsHideText, getStateID());
}

void KeyMappingState::makeEquipWeaponKeysTexts() const
{
	// Equip weapon key 1
	std::string equipWeaponKey1 = "Equip weapon key: ";
	equipWeaponText1.addComponent<TransformComponent>(500, 225, 17, 300, 1);
	equipWeaponText1.addComponent<TextComponent>("monoSmall", "equipWeaponText1",
		equipWeaponKey1.append(settings.getHumanReadableScancode(settings.equipWeapon1)));
	entityManager.addEntityToGroup(equipWeaponText1, getStateID());
}

void KeyMappingState::makePauseGameKeysTexts() const
{
	// Pause game key 1
	std::string pauseGameKey1 = "Pause game key 1: ";
	pauseGameText1.addComponent<TransformComponent>(500, 325, 17, 300, 1);
	pauseGameText1.addComponent<TextComponent>("monoSmall", "pauseGameText1",
		pauseGameKey1.append(settings.getHumanReadableScancode(settings.pauseGame1)));
	entityManager.addEntityToGroup(pauseGameText1, getStateID());
}

void KeyMappingState::makeShieldAndShootKeysTexts() const
{
	std::string activateShieldKey = "Activate shield: ";
	activateShieldText.addComponent<TransformComponent>(500, 425, 17, 300, 1);
	activateShieldText.addComponent<TextComponent>("monoSmall", "activateShieldText",
		activateShieldKey.append(settings.getHumanReadableScancode(settings.activateShield)));
	entityManager.addEntityToGroup(activateShieldText, getStateID());
}

void KeyMappingState::makeButtons()
{
	makeChangeMovementKeyButtons();
	makeChangeFPSKeyButtons();
	makeChangeEquipWeaponKeyButtons();
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

		changingKeyString = "Changing key: move left 1";
	});

	left1Button.addExistingComponent<ButtonComponent>(left1ButtonComponent);
	left1Button.addComponent<TransformComponent>(360, 218, 22, 44, 1);
	left1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(left1Button, getStateID());

	auto& right1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* right1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.right1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.right1;

		changingKeyString = "Changing key: move right 1";
	});

	right1Button.addExistingComponent<ButtonComponent>(right1ButtonComponent);
	right1Button.addComponent<TransformComponent>(360, 243, 22, 44, 1);
	right1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(right1Button, getStateID());

	auto& up1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* up1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.up1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.up1;

		changingKeyString = "Changing key: move up 1";
	});

	up1Button.addExistingComponent<ButtonComponent>(up1ButtonComponent);
	up1Button.addComponent<TransformComponent>(360, 268, 22, 44, 1);
	up1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(up1Button, getStateID());

	auto& down1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* down1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.down1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.down1;

		changingKeyString = "Changing key: move down 1";
	});

	down1Button.addExistingComponent<ButtonComponent>(down1ButtonComponent);
	down1Button.addComponent<TransformComponent>(360, 293, 22, 44, 1);
	down1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(down1Button, getStateID());

	auto& left2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* left2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.left2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.left2;

		changingKeyString = "Changing key: move left 2";
	});

	left2Button.addExistingComponent<ButtonComponent>(left2ButtonComponent);
	left2Button.addComponent<TransformComponent>(360, 318, 22, 44, 1);
	left2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(left2Button, getStateID());

	auto& right2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* right2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.right2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.right2;

		changingKeyString = "Changing key: move right 2";
	});

	right2Button.addExistingComponent<ButtonComponent>(right2ButtonComponent);
	right2Button.addComponent<TransformComponent>(360, 343, 22, 44, 1);
	right2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(right2Button, getStateID());

	auto& up2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* up2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.up2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.up2;

		changingKeyString = "Changing key: move up 2";
	});

	up2Button.addExistingComponent<ButtonComponent>(up2ButtonComponent);
	up2Button.addComponent<TransformComponent>(360, 368, 22, 44, 1);
	up2Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(up2Button, getStateID());

	auto& down2Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* down2ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.down2;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.down2;

		changingKeyString = "Changing key: move down 2";
	});

	down2Button.addExistingComponent<ButtonComponent>(down2ButtonComponent);
	down2Button.addComponent<TransformComponent>(360, 393, 22, 44, 1);
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

		changingKeyString = "Changing key: FPS up";
	});

	fpsSpdUpButton.addExistingComponent<ButtonComponent>(fpsSpdUpButtonComponent);
	fpsSpdUpButton.addComponent<TransformComponent>(310, 493, 22, 44, 1);
	fpsSpdUpButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsSpdUpButton, getStateID());

	auto& fpsSpdDownButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsSpdDownButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsSpdDown;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsSpdDown;

		changingKeyString = "Changing key: FPS down";
	});

	fpsSpdDownButton.addExistingComponent<ButtonComponent>(fpsSpdDownButtonComponent);
	fpsSpdDownButton.addComponent<TransformComponent>(310, 518, 22, 44, 1);
	fpsSpdDownButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsSpdDownButton, getStateID());

	auto& fpsResetButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsResetButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsSpdReset;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsSpdReset;

		changingKeyString = "Changing key: FPS reset";
	});

	fpsResetButton.addExistingComponent<ButtonComponent>(fpsResetButtonComponent);
	fpsResetButton.addComponent<TransformComponent>(310, 543, 22, 44, 1);
	fpsResetButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsResetButton, getStateID());

	auto& fpsShowButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsShowButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsShow;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsShow;

		changingKeyString = "Changing key: show FPS";
	});

	fpsShowButton.addExistingComponent<ButtonComponent>(fpsShowButtonComponent);
	fpsShowButton.addComponent<TransformComponent>(310, 568, 22, 44, 1);
	fpsShowButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(fpsShowButton, getStateID());

	auto& fpsHideButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* fpsHideButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.fpsHide;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.fpsHide;

		changingKeyString = "Changing key: hide FPS";
	});

	fpsHideButton.addExistingComponent<ButtonComponent>(fpsHideButtonComponent);
	fpsHideButton.addComponent<TransformComponent>(310, 593, 22, 44, 1);
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

		changingKeyString = "Changing key: equip weapon";
	});

	equipWeapon1Button.addExistingComponent<ButtonComponent>(equipWeapon1ButtonComponent);
	equipWeapon1Button.addComponent<TransformComponent>(810, 218, 22, 44, 1);
	equipWeapon1Button.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(equipWeapon1Button, getStateID());
}

void KeyMappingState::makeChangePauseKeyButtons()
{
	auto& pauseGame1Button = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* pauseGame1ButtonComponent = new ButtonComponent([this]()
	{
		inputHandler.newKey = settings.pauseGame1;
		inputHandler.isMappingKey(true);
		settings.keyToChange = settings.pauseGame1;

		changingKeyString = "Changing key: pause game";
	});

	pauseGame1Button.addExistingComponent<ButtonComponent>(pauseGame1ButtonComponent);
	pauseGame1Button.addComponent<TransformComponent>(810, 318, 22, 44, 1);
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

		changingKeyString = "Changing key: activate shield";
	});

	activateShieldButton.addExistingComponent<ButtonComponent>(activateShieldButtonComponent);
	activateShieldButton.addComponent<TransformComponent>(810, 418, 22, 44, 1);
	activateShieldButton.addComponent<ButtonSpriteComponent>("changeButton", 1, 3, 0, 1).setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(activateShieldButton, getStateID());
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
	exitButton.addComponent<TransformComponent>(10, 10, 64, 128, 1);
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

void KeyMappingState::updateChangingKeyText() const
{
	if (inputHandler.isMappingKey())
	{
		changingKeyText.getComponent<TextComponent>().setText(changingKeyString);
	}
	else
	{
		changingKeyText.getComponent<TextComponent>().setText(" ");
	}
}
