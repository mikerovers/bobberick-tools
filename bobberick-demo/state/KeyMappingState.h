#pragma once
#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/SettingsService.h"

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
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();

	void makeHeaders() const;
	void makeMovementKeysTexts() const;
	void makeFPSKeysTexts() const;
	void makeKeyTexts() const;
	void makeTexts() const;
};
