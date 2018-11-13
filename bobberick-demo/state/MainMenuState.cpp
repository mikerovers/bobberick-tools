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

std::string MainMenuState::getStateID() const
{
	return "mainmenu";
}

void MainMenuState::update()
{
	for (const auto &system : systems) {
		system->update();
	}
	determineMovementDirection();
}

bool MainMenuState::onEnter()
{
	createAnimatedBackground();

	for (const auto &system : systems) {
		system->init();
	}

	std::cout << "Entered MainMenuState" << std::endl;

	makeStartGameButton();
	makeOptionsButton();
	makeExitButton();

	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "Exited MainMenuState" << std::endl;

	// for (auto button : buttons)
	// {
	// 	delete button;
	// }
	
	// for (auto entity : entities)
	// {
	// 	delete entity;
	// }
	
	// delete[] buttons;
	// delete[] entities;

	return true;
}

bool MainMenuState::shouldExit()
{
	return _playGamePressed;
}

void MainMenuState::createAnimatedBackground()
{
	auto* fireWizard = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& fireWizardTransformComponent = fireWizard->addComponent<TransformComponent>(-1, 20, 59, 54, 2);
	fireWizard->addComponent<SpriteComponent>("assets/image/enemies/fire_wizard.png", "fire_wizard", 5, 5, 12);
	fireWizard->addComponent<CollisionComponent>("fireWizard");
	fireWizard->addComponent<AIComponent>();
	fireWizardTransformComponent.speed = 1.5;
	entities[0] = fireWizard;

	auto* zombie = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& zombieTransformComponent = zombie->addComponent<TransformComponent>(-1, 140, 51, 51, 2);
	zombie->addComponent<SpriteComponent>("assets/image/enemies/zombie.png", "zombie", 6, 4, 10);
	zombie->addComponent<CollisionComponent>("fireWizard");
	zombie->addComponent<AIComponent>();
	zombieTransformComponent.speed = 1.5;
	entities[1] = zombie;

	auto* orc = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& OrcTransformComponent = orc->addComponent<TransformComponent>(-1, 260, 49, 64, 2);
	orc->addComponent<SpriteComponent>("assets/image/enemies/orc_piratess.png", "orc", 9, 9, 3);
	orc->addComponent<CollisionComponent>("fireWizard");
	orc->addComponent<AIComponent>();
	OrcTransformComponent.speed = 1.5;
	entities[2] = orc;

	auto* player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& playerTransformComponent = player->addComponent<TransformComponent>(-1, 380, 64, 32, 2);
	player->addComponent<SpriteComponent>("assets/image/character.png", "character", 6, 4, 5);
	player->addComponent<CollisionComponent>("fireWizard");
	player->addComponent<AIComponent>();
	playerTransformComponent.speed = 1.5;
	entities[3] = player;
}

void MainMenuState::makeStartGameButton()
{
	auto* playGameButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto* playGameButtonComponent = new ButtonComponent([this]() {
		std::cout << "Play button clicked" << std::endl;
		_playGamePressed = true;
	});

	playGameButton->addExistingComponent<ButtonComponent>(playGameButtonComponent);
	auto* playGameButtonTransformComponent = new TransformComponent();
	playGameButtonTransformComponent->position.setX(260);
	playGameButtonTransformComponent->position.setY(60);
	playGameButtonTransformComponent->height = 64;
	playGameButtonTransformComponent->width = 128;
	playGameButton->addExistingComponent<TransformComponent>(playGameButtonTransformComponent);
	playGameButton->addComponent<ButtonSpriteComponent>("assets/image/button/startgamebutton.png", "startgamebutton", 1, 3, 0);
	playGameButton->getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	// buttons[0] = playGameButton;
}

void MainMenuState::makeOptionsButton()
{
	auto* optionsButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto* optionsButtonComponent = new ButtonComponent([this]() {
		std::cout << "Options button clicked" << std::endl;
		_playGamePressed = true;
	});

	optionsButton->addExistingComponent<ButtonComponent>(optionsButtonComponent);
	auto* optionsButtonTransformComponent = new TransformComponent();
	optionsButtonTransformComponent->position.setX(260);
	optionsButtonTransformComponent->position.setY(140);
	optionsButtonTransformComponent->height = 64;
	optionsButtonTransformComponent->width = 128;
	optionsButton->addExistingComponent<TransformComponent>(optionsButtonTransformComponent);
	optionsButton->addComponent<ButtonSpriteComponent>("assets/image/button/optionsbutton.png", "optionsbutton", 1, 3, 0);
	optionsButton->getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	
	// buttons[1] = optionsButton;
}

void MainMenuState::makeExitButton()
{
	auto* exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]() {
		std::cout << "Exit button clicked" << std::endl;
		_playGamePressed = true;
	});

	exitButton->addExistingComponent<ButtonComponent>(exitButtonComponent);
	auto* exitButtonTransformComponent = new TransformComponent();
	exitButtonTransformComponent->position.setX(260);
	exitButtonTransformComponent->position.setY(220);
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton->addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton->addComponent<ButtonSpriteComponent>("assets/image/button/exitbutton.png", "exitbutton", 1, 3, 0);
	exitButton->getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	
	// buttons[2] = exitButton;
}

void MainMenuState::determineMovementDirection()
{
	// if (player->getComponent<TransformComponent>().position.getX() < 150) {
	// 	player->getComponent<TransformComponent>().velocity.setX(0.2 * player->getComponent<TransformComponent>().speed);
	// 	player->getComponent<TransformComponent>().velocity.setY(0);
	// 	player->getComponent<SpriteComponent>().flip = false;
	// }
	// else if (player->getComponent<TransformComponent>().position.getX() > 500) { // TODO: find a better way to get the window width
	// 	player->getComponent<TransformComponent>().velocity.setX(-(0.2 * player->getComponent<TransformComponent>().speed));
	// 	player->getComponent<TransformComponent>().velocity.setY(0);
	// 	player->getComponent<SpriteComponent>().flip = true;
	// }
	//
	//
	//
	//
	// if (orc->getComponent<TransformComponent>().position.getX() < 150) {
	// 	orc->getComponent<TransformComponent>().velocity.setX(0.2 * orc->getComponent<TransformComponent>().speed);
	// 	orc->getComponent<TransformComponent>().velocity.setY(0);
	// 	orc->getComponent<SpriteComponent>().flip = false;
	// }
	// else if (orc->getComponent<TransformComponent>().position.getX() > 500) { // TODO: find a better way to get the window width
	// 	orc->getComponent<TransformComponent>().velocity.setX(-(0.2 * orc->getComponent<TransformComponent>().speed));
	// 	orc->getComponent<TransformComponent>().velocity.setY(0);
	// 	orc->getComponent<SpriteComponent>().flip = true;
	// }
	//
	//
	//
	//
	// if (zombie->getComponent<TransformComponent>().position.getX() < 150) {
	// 	zombie->getComponent<TransformComponent>().velocity.setX(0.2 * zombie->getComponent<TransformComponent>().speed);
	// 	zombie->getComponent<TransformComponent>().velocity.setY(0);
	// 	zombie->getComponent<SpriteComponent>().flip = false;
	// }
	// else if (zombie->getComponent<TransformComponent>().position.getX() > 500) { // TODO: find a better way to get the window width
	// 	zombie->getComponent<TransformComponent>().velocity.setX(-(0.2 * zombie->getComponent<TransformComponent>().speed));
	// 	zombie->getComponent<TransformComponent>().velocity.setY(0);
	// 	zombie->getComponent<SpriteComponent>().flip = true;
	// }
	//
	//
	//
	//
	// if (fireWizard->getComponent<TransformComponent>().position.getX() < 150) {
	// 	fireWizard->getComponent<TransformComponent>().velocity.setX(0.2 * fireWizard->getComponent<TransformComponent>().speed);
	// 	fireWizard->getComponent<TransformComponent>().velocity.setY(0);
	// 	fireWizard->getComponent<SpriteComponent>().flip = false;
	// }
	// else if (fireWizard->getComponent<TransformComponent>().position.getX() > 500) { // TODO: find a better way to get the window width
	// 	fireWizard->getComponent<TransformComponent>().velocity.setX(-(0.2 * fireWizard->getComponent<TransformComponent>().speed));
	// 	fireWizard->getComponent<TransformComponent>().velocity.setY(0);
	// 	fireWizard->getComponent<SpriteComponent>().flip = true;
	// }

	for (const auto& entity : entities)
	{
		auto& transform = entity->getComponent<TransformComponent>();
		auto& sprite = entity->getComponent<SpriteComponent>();
		const double speed = 0.2 * transform.speed;
		transform.velocity.setY(0);
	
		if (transform.position.getX() < 150) {
			transform.velocity.setX(speed);
			sprite.flip = false;
		} else if (transform.position.getX() > 500) { // TODO: find a better way to get the window width
			transform.velocity.setX(-speed);
			sprite.flip = true; 
		}
	}
}