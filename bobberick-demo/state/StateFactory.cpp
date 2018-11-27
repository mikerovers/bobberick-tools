#include "StateFactory.h"
#include <memory>
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../systems/HudSystem.h"
#include "../../bobberick-framework/src/entity/systems/GuiSystem.h"
#include "../../bobberick-framework/src/entity/systems/CollisionSystem.h"
#include "../systems/PlayerInputSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/AdvertisementSystem.h"
#include "../systems/CheatSystem.h"
#include "../state/TestState.h"
#include "../systems/ShieldSystem.h"
#include "../systems/LevelSystem.h"
#include "../state/CreditScreenState.h"
#include "../systems/AISystem.h"
#include "MainMenuState.h"

GameState* StateFactory::createState(const std::string& type)
{
	if (type == "SplashScreenState")
	{
		return createSplashScreenState();
	} 
	else if (type == "MainMenuState") {
		return createMainMenuState();
	}
	else if (type == "PauseScreenState") {
		return createPauseScreenState();
	}
	else if (type == "Level1State")
	{
		return createPlayState();
	} else if (type == "Level2State")
	{
		return createLevel2State();
	} else if (type == "Level3State")
    {
	    return createLevel3State();
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
	}
	else if (type == "EndScreen")
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

MainMenuState* StateFactory::createMainMenuState()
{
    MainMenuState * mainMenuState = new MainMenuState();
    mainMenuState->addSystem(
		std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
		std::make_shared<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
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

PauseScreenState *StateFactory::createPauseScreenState() const
{
	auto* pauseScreenState = new PauseScreenState();

	pauseScreenState->addSystem(
		std::make_shared<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	pauseScreenState->addSystem(
		std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	pauseScreenState->addSystem(
		std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	pauseScreenState->addSystem(
		std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return pauseScreenState;
}

Level1State* StateFactory::createPlayState()
{
	Level1State* playState = new Level1State();
	playState->addSystem(std::make_shared<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<CheatSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<LevelSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}

Level2State *StateFactory::createLevel2State() const
{
	Level2State* playState = new Level2State();
	playState->addSystem(std::make_shared<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<CheatSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<LevelSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}

Level3State *StateFactory::createLevel3State() const
{
	Level3State* playState = new Level3State();
	playState->addSystem(std::make_shared<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<CheatSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_shared<LevelSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}
