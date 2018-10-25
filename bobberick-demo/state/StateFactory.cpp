#include "StateFactory.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../systems/PlayerInputSystem.h"

GameState* StateFactory::createState(const std::string type) {
	if (type == "SplashScreenState") {
		return createSplashScreenState();
	} else if (type == "PlayState") {
		return createPlayState();
	}

	return nullptr;
}

SplashScreenState* StateFactory::createSplashScreenState() {
	SplashScreenState* splashScreen = new SplashScreenState();
	splashScreen->addSystem(std::shared_ptr<DrawSystem>(new DrawSystem(ServiceManager::Instance()->getService<EntityManager>())));

	return splashScreen;
}

PlayState *StateFactory::createPlayState()
{
	PlayState* playState = new PlayState();
	playState->addSystem(std::shared_ptr<InputSystem>(new InputSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<PlayerInputSystem>(new PlayerInputSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<DrawSystem>(new DrawSystem(ServiceManager::Instance()->getService<EntityManager>())));

	return playState;
}