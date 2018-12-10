#include <string>
#include "MainMenuState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../services/PlayerStatsService.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include <iostream>
#include "../factory/enemies/EnemyFactory.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../factory/ObjectFactory.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"
#include "../components/SpawnMinionsSpellComponent.h"
#include "../components/AdvertisementComponent.h"
#include "../components/SprayComponent.h"

std::string MainMenuState::getStateID() const
{
	return "mainmenu";
}

void MainMenuState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool MainMenuState::onEnter()
{
	createAnimatedBackground();

	readyForExit = false;

	ServiceManager::Instance()->getService<SoundManager>().playMusic("menu", -1);
	if (!ServiceManager::Instance()->getService<SettingsService>().music) {
		ServiceManager::Instance()->getService<SoundManager>().pauseMusic();
	}
	for (const auto& system : systems)
	{
		system->init();
	}

	std::cout << "Entered MainMenuState" << std::endl;

	makeStartGameButton();
	makeOptionsButton();
	makeScoresButton();
	makeExitButton();
	makeHelpButton();
	makeAdvertisements();

	if (ServiceManager::Instance()->getService<PlayerStatsService>().validateSave()) {
		makeLoadButton();
	}

	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "Exited MainMenuState" << std::endl;
	ServiceManager::Instance()->getService<SoundManager>().stopMusic();
	return true;
}

bool MainMenuState::shouldExit()
{
	return readyForExit;
}


void MainMenuState::createAnimatedBackground()
{
	EnemyFactory enemyFactory;

	auto& fireWizard = enemyFactory.getEnemy(1, "fireWizard");
	fireWizard.getComponent<TransformComponent>().position = Vector2D{20, 20};
	entityManager.addEntityToGroup(fireWizard, getStateID());
	entities.push_back(&fireWizard);

	auto& zombie = enemyFactory.getEnemy(1, "zombie");
	zombie.getComponent<TransformComponent>().position = Vector2D{560, 140};
	entityManager.addEntityToGroup(zombie, getStateID());
	entities.push_back(&zombie);

	auto& orc = enemyFactory.getEnemy(1, "orc");
	orc.getComponent<TransformComponent>().position = Vector2D{-1, 260};
	entityManager.addEntityToGroup(orc, getStateID());
	entities.push_back(&orc);

	auto& chicken = enemyFactory.getEnemy(10, "chicken");
	chicken.getComponent<TransformComponent>().position = Vector2D{300, 300};
	entityManager.addEntityToGroup(chicken, getStateID());
	entities.push_back(&chicken);
}

void MainMenuState::makeStartGameButton() const
{
	auto& playGameButton = entityManager.addEntity();
	auto* playGameButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("SkillScreenState"));
	});

	playGameButton.addExistingComponent<ButtonComponent>(playGameButtonComponent);
	playGameButton.addComponent<TransformComponent>(420, 60, 64, 128, 1);
	playGameButton.addComponent<ButtonSpriteComponent>("startGameButton", 1, 3, 0).setStaticAnimation(true);
	playGameButton.addComponent<CollisionComponent>("button");

	entityManager.addEntityToGroup(playGameButton, getStateID());
}

void MainMenuState::makeOptionsButton() const
{
	auto& optionsButton = entityManager.addEntity();
	auto* optionsButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("SettingsScreen"));
	});

	optionsButton.addExistingComponent<ButtonComponent>(optionsButtonComponent);
	optionsButton.addComponent<TransformComponent>(420, 140, 64, 128, 1);
	optionsButton.addComponent<ButtonSpriteComponent>("optionsButton", 1, 3, 0).setStaticAnimation(true);
	optionsButton.addComponent<CollisionComponent>("button");
	entityManager.addEntityToGroup(optionsButton, getStateID());
}

void MainMenuState::makeAdvertisements() const
{
	int const advertisementCount = ServiceManager::Instance()->getService<SettingsService>().advertisementCount - 1;
	auto& advertisement1 = entityManager.addEntity();
	advertisement1.addComponent<TransformComponent>(20, 450, 224, 300, 1);
	advertisement1.addComponent<SpriteComponent>("ad1");
	advertisement1.addComponent<AdvertisementComponent>(0, 0, advertisementCount);
	advertisement1.addComponent<TimerComponent>();
	advertisement1.addComponent<CollisionComponent>("advertisement");
	entityManager.addEntityToGroup(advertisement1, getStateID());

	auto& advertisement2 = entityManager.addEntity();
	advertisement2.addComponent<TransformComponent>(640, 450, 224, 300, 1);
	advertisement2.addComponent<SpriteComponent>("ad3");
	advertisement2.addComponent<AdvertisementComponent>(2, 0, advertisementCount);
	advertisement2.addComponent<TimerComponent>();
	advertisement2.addComponent<CollisionComponent>("advertisement");
	entityManager.addEntityToGroup(advertisement2, getStateID());
}

void MainMenuState::makeExitButton()
{
	auto& exitButton = entityManager.addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		readyForExit = true;
		std::cout << "Exit button clicked" << std::endl;
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	exitButton.addComponent<TransformComponent>(420, 460, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0).setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("button");

	entityManager.addEntityToGroup(exitButton, getStateID());
}

void MainMenuState::makeHelpButton() const
{
	auto& helpButton = entityManager.addEntity();
	auto* helpButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("HelpScreen"));
	});

	helpButton.addExistingComponent<ButtonComponent>(helpButtonComponent);
	helpButton.addComponent<TransformComponent>(420, 220, 64, 128, 1);
	helpButton.addComponent<ButtonSpriteComponent>("helpButton", 1, 3, 0).setStaticAnimation(true);
	entityManager.addEntityToGroup(helpButton, getStateID());
}

void MainMenuState::makeScoresButton() const
{
	auto& scoresButton = entityManager.addEntity();
	auto* scoresButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("HighscoreScreen"));
	});

	scoresButton.addExistingComponent<ButtonComponent>(scoresButtonComponent);
	scoresButton.addComponent<TransformComponent>(420, 300, 64, 128, 1);
	scoresButton.addComponent<ButtonSpriteComponent>("scoresButton", 1, 3, 0).setStaticAnimation(true);
	entityManager.addEntityToGroup(scoresButton, getStateID());
}

void MainMenuState::makeLoadButton() const
{
	auto& loadGameButton = entityManager.addEntity();
	auto* loadGameButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("Level1State"));
		ServiceManager::Instance()->getService<PlayerStatsService>().init();
		ServiceManager::Instance()->getService<PlayerStatsService>().load();
	});

	loadGameButton.addExistingComponent<ButtonComponent>(loadGameButtonComponent);
	loadGameButton.addComponent<TransformComponent>(420, 380, 64, 128, 1);
	loadGameButton.addComponent<ButtonSpriteComponent>("loadGameButton", 1, 3, 0).setStaticAnimation(true);
	loadGameButton.addComponent<CollisionComponent>("loadButton");

	entityManager.addEntityToGroup(loadGameButton, getStateID());
}
