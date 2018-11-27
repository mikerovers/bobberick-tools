#include <string>
#include "SkillScreenState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include <iostream>
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"

std::string SkillScreenState::getStateID() const
{
	return "skillscreen";
}

void SkillScreenState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool SkillScreenState::onEnter()
{
	for (const auto& system : systems)
	{
		system->init();
	}

	std::cout << "Entered SkillScreenState" << std::endl;

	skills = SkillsComponent(9999999, 0, 0, 0, 0, 0);

	makeStartGameButton();
	makeHpButton();
	makeAtButton();
	makeExitButton();
	return true;
}

bool SkillScreenState::onExit()
{
	std::cout << "Exited SkillScreenState" << std::endl;
	return true;
}

bool SkillScreenState::shouldExit()
{
	return readyForExit;
}

void SkillScreenState::makeStartGameButton()
{
	auto& playGameButton = entityManager.addEntity();
	auto* playGameButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("PlayState"));
	});

	playGameButton.addExistingComponent<ButtonComponent>(playGameButtonComponent);
	auto* playGameButtonTransformComponent = new TransformComponent();
	playGameButtonTransformComponent->position.x = 550;
	playGameButtonTransformComponent->position.y = 150;
	playGameButtonTransformComponent->height = 64;
	playGameButtonTransformComponent->width = 128;
	playGameButton.addExistingComponent<TransformComponent>(playGameButtonTransformComponent);
	playGameButton.addComponent<ButtonSpriteComponent>("startGameButton", 1,
	                                                   3, 0);
	playGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	entityManager.addEntityToGroup(playGameButton, getStateID());
}

void SkillScreenState::makeHpButton()
{
	auto& optionsButton = entityManager.addEntity();
	auto* optionsButtonComponent = new ButtonComponent([]()
	{
		std::cout << "Options button clicked" << std::endl;
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
	entityManager.addEntityToGroup(optionsButton, getStateID());
}

void SkillScreenState::makeAtButton()
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


void SkillScreenState::makeExitButton()
{
	auto& exitButton = entityManager.addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		readyForExit = true;
		std::cout << "Exit button clicked" << std::endl;
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	auto* exitButtonTransformComponent = new TransformComponent();

	exitButtonTransformComponent->position.x = 290;
	exitButtonTransformComponent->position.y = 150;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	entityManager.addEntityToGroup(exitButton, getStateID());
}

