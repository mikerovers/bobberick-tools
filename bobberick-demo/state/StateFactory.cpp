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
#include "../systems/MenuSystem.h"
#include "../state/TestState.h"
#include "../systems/ShieldSystem.h"
#include "../systems/LevelSystem.h"
#include "../systems/AISystem.h"
#include "MainMenuState.h"
#include "GameOverState.h"

std::unique_ptr<GameState> StateFactory::createState(const std::string& type)
{
	if (type == "SplashScreenState")
	{
		return createSplashScreenState();
	}
	else if (type == "MainMenuState")
	{
		return createMainMenuState();
	}
	else if (type == "PauseScreenState")
	{
		return createPauseScreenState();
	}
	else if (type == "Level1State")
	{
		return createPlayState();
	}
	else if (type == "Level2State")
	{
		return createLevel2State();
	}
	else if (type == "Level3State")
	{
		return createLevel3State();
	}
	else if (type == "TestState")
	{
		return std::make_unique<TestState>();
	}
	else if (type == "CreditScreenState")
	{
		return createCreditScreenState();
	}
	else if (type == "HelpScreen")
	{
		return createHelpScreenState();
	}
	else if (type == "EndScreen")
	{
		return createEndScreenState();
	}
	else if (type == "GameOverState")
	{
		return createGameOverState();
	}
	else if (type == "SettingsScreen")
	{
		return createSettingsScreenState();
	}
	else if (type == "SkillScreenState")
	{
		return createSkillScreenState();
	}
	else if (type == "HighscoreScreen")
	{
		return createHighscoreState();
	}
	else if (type == "KeyMappingScreen")
	{
		return createKeyMappingState();
	}

	return nullptr;
}

std::unique_ptr<SplashScreenState> StateFactory::createSplashScreenState()
{
	auto splashScreen = std::make_unique<SplashScreenState>();
	splashScreen->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	splashScreen->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return splashScreen;
}

std::unique_ptr<MainMenuState> StateFactory::createMainMenuState()
{
	auto mainMenuState = std::make_unique<MainMenuState>();
	mainMenuState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(std::make_unique<CollisionSystem>(
		ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
		std::make_unique<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
		std::make_unique<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	mainMenuState->addSystem(
		std::make_unique<AdvertisementSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return mainMenuState;
}

std::unique_ptr<SettingsScreenState> StateFactory::createSettingsScreenState() const
{
	auto settingsScreenState = std::make_unique<SettingsScreenState>();
	settingsScreenState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	settingsScreenState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	settingsScreenState->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	settingsScreenState->addSystem(
		std::make_unique<MenuSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return settingsScreenState;
}

std::unique_ptr<CreditScreenState> StateFactory::createCreditScreenState() const
{
	auto creditScreen = std::make_unique<CreditScreenState>();
	creditScreen->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	creditScreen->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return creditScreen;
}

std::unique_ptr<HelpScreenState> StateFactory::createHelpScreenState() const
{
	auto helpScreenState = std::make_unique<HelpScreenState>();

	helpScreenState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	helpScreenState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	helpScreenState->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	helpScreenState->addSystem(std::make_unique<CollisionSystem>(
		ServiceManager::Instance()->getService<EntityManager>()));

	return helpScreenState;
}

std::unique_ptr<EndScreenState> StateFactory::createEndScreenState() const
{
	auto endScreenState = std::make_unique<EndScreenState>();
	endScreenState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	endScreenState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	endScreenState->addSystem(
		std::make_unique<DrawSystem>((ServiceManager::Instance()->getService<EntityManager>())));
	endScreenState->addSystem(std::make_unique<CollisionSystem>(
		(ServiceManager::Instance()->getService<EntityManager>())));
	endScreenState->addSystem(
		std::make_unique<AISystem>((ServiceManager::Instance()->getService<EntityManager>())));

	return endScreenState;
}

std::unique_ptr<PauseScreenState> StateFactory::createPauseScreenState() const
{
	auto pauseScreenState = std::make_unique<PauseScreenState>();

	pauseScreenState->addSystem(
		std::make_unique<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	pauseScreenState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	pauseScreenState->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	pauseScreenState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return pauseScreenState;
}

std::unique_ptr<SkillScreenState> StateFactory::createSkillScreenState() const
{
	auto skillScreenState = std::make_unique<SkillScreenState>();
	skillScreenState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	skillScreenState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	skillScreenState->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return skillScreenState;
}

std::unique_ptr<Level1State> StateFactory::createPlayState()
{
	auto playState = std::make_unique<Level1State>();
	playState->addSystem(std::make_unique<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<CheatSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<LevelSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}

std::unique_ptr<Level2State> StateFactory::createLevel2State() const
{
	auto playState = std::make_unique<Level2State>();
	playState->addSystem(std::make_unique<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<CheatSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<LevelSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}

std::unique_ptr<Level3State> StateFactory::createLevel3State() const
{
	auto playState = std::make_unique<Level3State>();
	playState->addSystem(std::make_unique<CollisionSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<PlayerInputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<BulletSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<ShieldSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<HudSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<AISystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<CheatSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	playState->addSystem(std::make_unique<LevelSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return playState;
}

std::unique_ptr<GameOverState> StateFactory::createGameOverState() const
{
	auto gameOverState = std::make_unique<GameOverState>();

	gameOverState->addSystem(std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	gameOverState->addSystem(std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	gameOverState->addSystem(std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return gameOverState;
}

std::unique_ptr<HighscoreState> StateFactory::createHighscoreState() const
{
	auto highscoreState = std::make_unique<HighscoreState>();

	highscoreState->addSystem(std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	highscoreState->addSystem(std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	highscoreState->addSystem(std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return highscoreState;
}

std::unique_ptr<KeyMappingState> StateFactory::createKeyMappingState() const
{
	auto keyMappingState = std::make_unique<KeyMappingState>();

	keyMappingState->addSystem(
		std::make_unique<InputSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	keyMappingState->addSystem(
		std::make_unique<GuiSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	keyMappingState->addSystem(
		std::make_unique<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	keyMappingState->addSystem(
		std::make_unique<MenuSystem>(ServiceManager::Instance()->getService<EntityManager>()));

	return keyMappingState;
}
