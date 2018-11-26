#include "StateFactory.h"
#include <memory>
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../systems/HudSystem.h"
#include "../../bobberick-framework/src/entity/systems/GuiSystem.h"
#include "../../bobberick-framework/src/entity/systems/CollisionSystem.h"
#include "../systems/PlayerInputSystem.h"
#include "../systems/AdvertisementSystem.h"
#include "../systems/BulletSystem.h"
#include "../state/TestState.h"
#include "../systems/ShieldSystem.h"
#include "../state/CreditScreenState.h"
#include "../systems/AISystem.h"
#include "MainMenuState.h"

GameState* StateFactory::createState(const std::string& type)
{
	if (type == "SplashScreenState")
	{
		return createSplashScreenState();
	} else if (type == "MainMenuState") {
		return createMainMenuState();
	}
	else if (type == "PlayState")
	{
		return createPlayState();
	}
	else if (type == "TestState") {
		return new TestState();
	}
	else if (type == "CreditScreenState")
	{
		return createCreditScreenState();
	} else if (type == "HelpScreen")
	{
		return createHelpScreenState();
	} else if (type == "EndScreen")
	{
		return createEndScreenState();
	}

	return nullptr;
}

SplashScreenState* StateFactory::createSplashScreenState()
{
	SplashScreenState* splashScreen = new SplashScreenState();
	splashScreen->addSystem(
		std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	splashScreen->addSystem(
		std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return splashScreen;
}

PlayState* StateFactory::createPlayState()
{
	PlayState* playState = new PlayState();
	playState->addSystem(std::make_shared<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}

MainMenuState* StateFactory::createMainMenuState()
{
    MainMenuState * mainMenuState = new MainMenuState();
    mainMenuState->addSystem(
	    std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
    mainMenuState->addSystem(
	    std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
    mainMenuState->addSystem(
	    std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
    mainMenuState->addSystem(std::make_shared<CollisionSystem>(
	    ServiceManager::Instance()->getService<EntityManager>()));
    mainMenuState->addSystem(
	    std::make_shared<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
	    std::make_shared<AdvertisementSystem>(ServiceManager::Instance()->getService<EntityManager>()));

    return mainMenuState;
}

CreditScreenState* StateFactory::createCreditScreenState() const
{
	auto creditScreen = new CreditScreenState();
	creditScreen->addSystem(
			std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	creditScreen->addSystem(
		std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return creditScreen;
}

HelpScreenState *StateFactory::createHelpScreenState() const
{
	auto* helpScreenState = new HelpScreenState();

	helpScreenState->addSystem(
		std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	helpScreenState->addSystem(
		std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	helpScreenState->addSystem(
		std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	helpScreenState->addSystem(std::make_shared<CollisionSystem>(
		ServiceManager::Instance()->getService<EntityManager>()));

	return helpScreenState;
}

EndScreenState *StateFactory::createEndScreenState() const
{
	auto *endScreenState = new EndScreenState();
	endScreenState->addSystem(
			std::shared_ptr<InputSystem>(new InputSystem(ServiceManager::Instance()->getService<EntityManager>())));
	endScreenState->addSystem(
			std::shared_ptr<GuiSystem>(new GuiSystem(ServiceManager::Instance()->getService<EntityManager>())));
	endScreenState->addSystem(
			std::shared_ptr<DrawSystem>(new DrawSystem(ServiceManager::Instance()->getService<EntityManager>())));
	endScreenState->addSystem(std::shared_ptr<CollisionSystem>(
			new CollisionSystem(ServiceManager::Instance()->getService<EntityManager>())));
	endScreenState->addSystem(
			std::shared_ptr<AISystem>(new AISystem(ServiceManager::Instance()->getService<EntityManager>())));

	return endScreenState;
}
