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
	makeExitButton();
	makeHelpButton();
	makeAdvertisements();
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

	auto& fireWizard = enemyFactory.getEnemy(10, "fireWizard");
	fireWizard.getComponent<TransformComponent>().position = Vector2D{20, 20};
	entityManager.addEntityToGroup(fireWizard, getStateID());
	entities.push_back(&fireWizard);

	auto& zombie = enemyFactory.getEnemy(10, "zombie");
	zombie.getComponent<TransformComponent>().position = Vector2D{560, 140};
	entityManager.addEntityToGroup(zombie, getStateID());
	entities.push_back(&zombie);

	auto& orc = enemyFactory.getEnemy(10, "orc");
	orc.getComponent<TransformComponent>().position = Vector2D{-1, 260};
	entityManager.addEntityToGroup(orc, getStateID());
	entities.push_back(&orc);

	auto& chicken = enemyFactory.getEnemy(10, "chicken");
	chicken.getComponent<TransformComponent>().position = Vector2D{300, 300};
	entityManager.addEntityToGroup(chicken, getStateID());
	entities.push_back(&chicken);

	//auto& boss = enemyFactory.getBoss(10);
	//boss.getComponent<TransformComponent>().position = Vector2D{500, 350};
	//entityManager.addEntityToGroup(boss, getStateID());
	//entities.push_back(&boss);
}

void MainMenuState::makeStartGameButton()
{
	auto& playGameButton = entityManager.addEntity();
	auto* playGameButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<PlayerStatsService>().init();
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("SkillScreenState"));
	});

	playGameButton.addExistingComponent<ButtonComponent>(playGameButtonComponent);
	auto* playGameButtonTransformComponent = new TransformComponent();
	playGameButtonTransformComponent->position.x = 420;
	playGameButtonTransformComponent->position.y = 60;
	playGameButtonTransformComponent->height = 64;
	playGameButtonTransformComponent->width = 128;
	playGameButton.addExistingComponent<TransformComponent>(playGameButtonTransformComponent);
	playGameButton.addComponent<ButtonSpriteComponent>("startGameButton", 1,
	                                                   3, 0);
	playGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	playGameButton.addComponent<CollisionComponent>("button");

	entityManager.addEntityToGroup(playGameButton, getStateID());
}

void MainMenuState::makeOptionsButton()
{
	auto& optionsButton = entityManager.addEntity();
	auto* optionsButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("SettingsScreen"));
	});

	optionsButton.addExistingComponent<ButtonComponent>(optionsButtonComponent);
	auto* optionsButtonTransformComponent = new TransformComponent();
	optionsButtonTransformComponent->position.x = 420;
	optionsButtonTransformComponent->position.y = 140;
	optionsButtonTransformComponent->height = 64;
	optionsButtonTransformComponent->width = 128;
	optionsButton.addExistingComponent<TransformComponent>(optionsButtonTransformComponent);
	optionsButton.addComponent<ButtonSpriteComponent>("optionsButton", 1, 3, 0);
	optionsButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	optionsButton.addComponent<CollisionComponent>("button");
	entityManager.addEntityToGroup(optionsButton, getStateID());
}

void MainMenuState::makeAdvertisements()
{
	auto& advertisement1 = entityManager.addEntity();
	advertisement1.addComponent<TransformComponent>(20, 450, 224, 300, 1);
	advertisement1.addComponent<SpriteComponent>("ad1");
	advertisement1.addComponent<AdvertisementComponent>(1, 1, 5);
	advertisement1.addComponent<TimerComponent>();
	advertisement1.addComponent<CollisionComponent>("advertisement");
	entityManager.addEntityToGroup(advertisement1, getStateID());

	auto& advertisement2 = entityManager.addEntity();
	advertisement2.addComponent<TransformComponent>(640, 450, 224, 300, 1);
	advertisement2.addComponent<SpriteComponent>("ad3");
	advertisement2.addComponent<AdvertisementComponent>(3, 1, 5);
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
	auto* exitButtonTransformComponent = new TransformComponent();

	exitButtonTransformComponent->position.x = 420;
	exitButtonTransformComponent->position.y = 300;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("button");

	entityManager.addEntityToGroup(exitButton, getStateID());
}

void MainMenuState::makeHelpButton()
{
	auto& helpButton = entityManager.addEntity();
	auto* helpButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("HelpScreen"));
	});

	helpButton.addExistingComponent<ButtonComponent>(helpButtonComponent);
	auto* helpButtonTransformComponent = new TransformComponent();
	helpButtonTransformComponent->position.x = 420;
	helpButtonTransformComponent->position.y = 220;
	helpButtonTransformComponent->height = 64;
	helpButtonTransformComponent->width = 128;
	helpButton.addExistingComponent<TransformComponent>(helpButtonTransformComponent);
	helpButton.addComponent<ButtonSpriteComponent>("helpButton", 1, 3, 0);
	helpButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(helpButton, getStateID());
}
