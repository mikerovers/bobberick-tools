#ifndef BOBBERICK_TOOLS_KEYMAPPINGSTATE_H
#define BOBBERICK_TOOLS_KEYMAPPINGSTATE_H

#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/services/SaveService.h"

class KeyMappingState : public GameState
{
public:
	bool onEnter() override;
	bool onExit() override;
	void update() override;
	std::string getStateID() const override;
	bool shouldExit() override;

private:
	bool readyForExit = false;

	std::string changingKeyString;

	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	InputHandler& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	SettingsService& settings = ServiceManager::Instance()->getService<SettingsService>();
	SaveService& save = ServiceManager::Instance()->getService<SaveService>();

	Entity& moveLeftText1 = entityManager.addEntity();
	Entity& moveRightText1 = entityManager.addEntity();
	Entity& moveUpText1 = entityManager.addEntity();
	Entity& moveDownText1 = entityManager.addEntity();
	Entity& moveLeftText2 = entityManager.addEntity();
	Entity& moveRightText2 = entityManager.addEntity();
	Entity& moveUpText2 = entityManager.addEntity();
	Entity& moveDownText2 = entityManager.addEntity();

	Entity& fpsUpText = entityManager.addEntity();
	Entity& fpsDownText = entityManager.addEntity();
	Entity& fpsResetText = entityManager.addEntity();
	Entity& fpsShowText = entityManager.addEntity();
	Entity& fpsHideText = entityManager.addEntity();

	Entity& equipWeaponText1 = entityManager.addEntity();

	Entity& pauseGameText1 = entityManager.addEntity();

	Entity& activateShieldText = entityManager.addEntity();

	Entity& changingKeyText = entityManager.addEntity();

	void makeBackground() const;
	void makeHeaders() const;
	void makeShieldAndShootKeysTexts() const;
	void makeChangeShieldAndShootingKeyButtons();
	void makeMovementKeysTexts() const;
	void makeFPSKeysTexts() const;
	void makeEquipWeaponKeysTexts() const;
	void makePauseGameKeysTexts() const;
	void makeExitButton();
	void makeChangePauseKeyButtons();
	void makeChangeEquipWeaponKeyButtons();
	void makeChangeFPSKeyButtons();
	void makeChangeMovementKeyButtons();
	void updatePauseGameKeysTexts() const;
	void updateEquipWeaponKeysTexts() const;
	void updateFPSKeysTexts() const;
	void updateMovementKeysTexts() const;
	void updateShieldAndShootingKeysTexts() const;
	void updateChangingKeyText() const;
	void makeKeyTexts() const;
	void makeTexts() const;
	void makeButtons();
};

#endif //BOBBERICK_TOOLS_KEYMAPPINGSTATE_H