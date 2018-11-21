#include <string>
#include "MainMenuState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include <iostream>
#include "../factory/enemies/EnemyFactory.h"
#include "../components/AIComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../factory/ObjectFactory.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"

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
	determineMovementDirection();
}

bool MainMenuState::onEnter()
{
	createAnimatedBackground();

	for (const auto& system : systems)
	{
		system->init();
	}

	std::cout << "Entered MainMenuState" << std::endl;

	makeStartGameButton();
	makeOptionsButton();
	makeExitButton();
	makeHelpButton();

	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "Exited MainMenuState" << std::endl;

	return true;
}

bool MainMenuState::shouldExit()
{
	return false;
}

Entity& MainMenuState::makeTileMap() const
{
	auto& level = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	// Use LevelFactory to load and create tilemap components.
	auto* levelFactory = new LevelFactory();
	TilesetComponent* tilesetComponent = levelFactory->Load("assets/maps/main_menu.tmx",
	                                                        ServiceManager::Instance()
	                                                        ->getService<RenderService>().getRenderer());

	level.addExistingComponent<TilesetComponent>(tilesetComponent);
	delete levelFactory;

	ObjectFactory objectFactory;
	for (auto& object : level.getComponent<TilesetComponent>().objects)
	{
		objectFactory.getObject(object);
	}

	return level;
}


void MainMenuState::createAnimatedBackground()
{
	auto& fireWizard = entityManager.addEntity();
	auto& fireWizardTransformComponent = fireWizard.addComponent<TransformComponent>(-1, 20, 59, 54, 2);
	fireWizard.addComponent<SpriteComponent>("assets/image/enemies/fire_wizard.png", "fire_wizard", 5, 5, 12);
	fireWizard.addComponent<CollisionComponent>("fireWizard");
	fireWizard.addComponent<AIComponent>();
	fireWizardTransformComponent.speed = 1.5;
	entityManager.addEntityToGroup(fireWizard, getStateID());
	entities.push_back(&fireWizard);

	auto& zombie = entityManager.addEntity();
	auto& zombieTransformComponent = zombie.addComponent<TransformComponent>(560, 140, 51, 51, 2);
	zombie.addComponent<SpriteComponent>("assets/image/enemies/zombie.png", "zombie", 6, 4, 10);
	zombie.addComponent<CollisionComponent>("fireWizard");
	zombie.addComponent<AIComponent>();
	zombieTransformComponent.speed = -1.5;
	entityManager.addEntityToGroup(zombie, getStateID());
	entities.push_back(&zombie);

	auto& orc = entityManager.addEntity();
	auto& OrcTransformComponent = orc.addComponent<TransformComponent>(-1, 260, 49, 64, 2);
	orc.addComponent<SpriteComponent>("assets/image/enemies/orc_piratess.png", "orc", 9, 9, 3);
	orc.addComponent<CollisionComponent>("fireWizard");
	orc.addComponent<AIComponent>();
	OrcTransformComponent.speed = 1.5;
	entityManager.addEntityToGroup(orc, getStateID());
	entities.push_back(&orc);

	auto& player = entityManager.addEntity();
	auto& playerTransformComponent = player.addComponent<TransformComponent>(560, 380, 64, 32, 2);
	player.addComponent<SpriteComponent>("assets/image/character.png", "character", 6, 4, 5);
	player.addComponent<CollisionComponent>("fireWizard");
	player.addComponent<AIComponent>();
	playerTransformComponent.speed = -1.5;
	entityManager.addEntityToGroup(player, getStateID());
	entities.push_back(&player);
}

void MainMenuState::makeStartGameButton()
{
	auto& playGameButton = entityManager.addEntity();
	auto* playGameButtonComponent = new ButtonComponent([this]()
	{
        StateFactory factory{};
        ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("PlayState"));
	});

	playGameButton.addExistingComponent<ButtonComponent>(playGameButtonComponent);
	auto* playGameButtonTransformComponent = new TransformComponent();
	playGameButtonTransformComponent->position.x = 260;
	playGameButtonTransformComponent->position.y = 60;
	playGameButtonTransformComponent->height = 64;
	playGameButtonTransformComponent->width = 128;
	playGameButton.addExistingComponent<TransformComponent>(playGameButtonTransformComponent);
	playGameButton.addComponent<ButtonSpriteComponent>("assets/image/button/startgamebutton.png", "startgamebutton", 1,
	                                                   3, 0);
	playGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(playGameButton, getStateID());
}

void MainMenuState::makeOptionsButton()
{
	auto& optionsButton = entityManager.addEntity();
	auto* optionsButtonComponent = new ButtonComponent([this]()
	{
		std::cout << "Options button clicked" << std::endl;
	});

	optionsButton.addExistingComponent<ButtonComponent>(optionsButtonComponent);
	auto* optionsButtonTransformComponent = new TransformComponent();
	optionsButtonTransformComponent->position.x = 260;
	optionsButtonTransformComponent->position.y= 140;
	optionsButtonTransformComponent->height = 64;
	optionsButtonTransformComponent->width = 128;
	optionsButton.addExistingComponent<TransformComponent>(optionsButtonTransformComponent);
	optionsButton.addComponent<ButtonSpriteComponent
	>("assets/image/button/optionsbutton.png", "optionsbutton", 1, 3, 0);
	optionsButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(optionsButton, getStateID());
}

void MainMenuState::makeExitButton()
{
	auto& exitButton = entityManager.addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		std::cout << "Exit button clicked" << std::endl;
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	auto* exitButtonTransformComponent = new TransformComponent();

	exitButtonTransformComponent->position.x = 260;
	exitButtonTransformComponent->position.y = 300;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("assets/image/button/exitbutton.png", "exitbutton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(exitButton, getStateID());
}

void MainMenuState::determineMovementDirection()
{
	for (const auto& entity : entities)
	{
		auto& transform = entity->getComponent<TransformComponent>();
		auto& sprite = entity->getComponent<SpriteComponent>();
		const double speed = 0.2 * transform.speed;
		transform.velocity.y = 0;

		if (transform.position.x < 150)
		{
			transform.velocity.x = speed;
			sprite.flip = false;
		}
		else if (transform.position.x > 500)
		{
			// TODO: find a better way to get the window width
			transform.velocity.x = -speed;
			sprite.flip = true;
		}
	}
}

void MainMenuState::makeHelpButton()
{
	auto& helpButton = entityManager.addEntity();
	auto* helpButtonComponent = new ButtonComponent([this]()
    {
        StateFactory factory{};
        ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("HelpScreen"));
    });

	helpButton.addExistingComponent<ButtonComponent>(helpButtonComponent);
	auto* helpButtonTransformComponent = new TransformComponent();
	helpButtonTransformComponent->position.x = 260;
	helpButtonTransformComponent->position.y = 220;
	helpButtonTransformComponent->height = 64;
	helpButtonTransformComponent->width = 128;
	helpButton.addExistingComponent<TransformComponent>(helpButtonTransformComponent);
	helpButton.addComponent<ButtonSpriteComponent>("assets/image/button/helpbutton.png", "helpbutton", 1, 3, 0);
	helpButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(helpButton, getStateID());
}
