#include <string>
#include "MainMenuState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include <iostream>

std::string MainMenuState::getStateID() const
{
	return "mainmenu";
}

void MainMenuState::update()
{
	for (const auto &system : systems) {
		system->update();
	}
}

bool MainMenuState::onEnter()
{
	for (const auto &system : systems) {
		system->init();
	}

	std::cout << "Entered MainMenuState" << std::endl;

	makeStartGameButton();
	makeExitButton();

	return true;
}

bool MainMenuState::onExit()
{
	std::cout << "Exited MainMenuState" << std::endl;

	return true;
}

bool MainMenuState::shouldExit()
{
	return _playGamePressed;
}

void MainMenuState::makeStartGameButton()
{
	std::shared_ptr<Entity> playGameButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
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
	playGameButton->addComponent<ButtonSpriteComponent>("assets/image/button/startgamebutton-old.png", "startgamebutton", 1, 3, 0);
	playGameButton->getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
}

void MainMenuState::makeExitButton()
{
	std::shared_ptr<Entity> exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]() {
		std::cout << "Exit button clicked" << std::endl;
		_playGamePressed = true;
	});

	exitButton->addExistingComponent<ButtonComponent>(exitButtonComponent);
	auto* exitButtonTransformComponent = new TransformComponent();
	exitButtonTransformComponent->position.setX(260);
	exitButtonTransformComponent->position.setY(140);
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton->addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton->addComponent<ButtonSpriteComponent>("assets/image/button/exitbutton.png", "exitbutton", 1, 3, 0);
	exitButton->getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
}
