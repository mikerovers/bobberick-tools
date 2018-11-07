#include "StateFactory.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../../bobberick-framework/src/entity/systems/CollisionSystem.h"
#include "../systems/HudSystem.h"
#include "../../bobberick-framework/src/entity/systems/GuiSystem.h"
#include "../../bobberick-framework/src/entity/systems/CollisionSystem.h"
#include "../systems/PlayerInputSystem.h"
#include "../systems/BulletSystem.h"

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
	playState->addSystem(std::shared_ptr<BulletSystem>(new BulletSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<DrawSystem>(new DrawSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<CollisionSystem>(new CollisionSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<HudSystem>(new HudSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<GuiSystem>(new GuiSystem(ServiceManager::Instance()->getService<EntityManager>())));
	playState->addSystem(std::shared_ptr<CollisionSystem>(new CollisionSystem(ServiceManager::Instance()->getService<EntityManager>())));

	return playState;
}
