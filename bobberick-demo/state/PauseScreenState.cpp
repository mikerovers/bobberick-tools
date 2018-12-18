#include "PauseScreenState.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "StateFactory.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../services/PlayerStatsService.h"

std::string PauseScreenState::getStateID() const
{
	return "pause";
}

void PauseScreenState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool PauseScreenState::onExit()
{
	std::cout << "Exited PauseScreenState" << std::endl;
	ServiceManager::Instance()->getService<SoundManager>().resumeAllChannels();
	return true;
}

bool PauseScreenState::shouldExit()
{
	return readyForExit;
}

bool PauseScreenState::onEnter()
{
	createPauseText();
	createResumeButton();
	makeOptionsButton();
	createSaveButton();
	// createLoadButton();
	createHelpButton();
	createExitButton();
	ServiceManager::Instance()->getService<SoundManager>().pauseAllChannels();
	return true;
}

void PauseScreenState::createPauseText() const
{
	auto& pauseText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	pauseText.addComponent<TransformComponent>(300, 30, 80, 360, 1);
	pauseText.addComponent<TextComponent>("defaultLarge", "pauseText", "Game paused");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(pauseText, getStateID());
}

void PauseScreenState::createResumeButton() const
{
	auto& resumeGameButton = entityManager.addEntity();
	auto* resumeGameButtonComponent = new ButtonComponent([]()
	{
		ServiceManager::Instance()->getService<StateMachine>().popState();
	});

	resumeGameButton.addExistingComponent<ButtonComponent>(resumeGameButtonComponent);
	resumeGameButton.addComponent<TransformComponent>(420, 140, 64, 128, 1);
	resumeGameButton.addComponent<ButtonSpriteComponent>("resumeGameButton", 1, 3, 0, 1).setStaticAnimation(true);
	resumeGameButton.addComponent<CollisionComponent>("resumeButton");

	entityManager.addEntityToGroup(resumeGameButton, getStateID());
}

void PauseScreenState::makeOptionsButton() const
{
	auto& optionsButton = entityManager.addEntity();
	auto* optionsButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("SettingsScreen"));
	});

	optionsButton.addExistingComponent<ButtonComponent>(optionsButtonComponent);
	optionsButton.addComponent<TransformComponent>(420, 220, 64, 128, 1);
	optionsButton.addComponent<ButtonSpriteComponent>("optionsButton", 1, 3, 0, 1).setStaticAnimation(true);
	optionsButton.addComponent<CollisionComponent>("button");
	entityManager.addEntityToGroup(optionsButton, getStateID());
}

void PauseScreenState::createSaveButton() const
{
	auto& saveGameButton = entityManager.addEntity();
	auto* saveGameButtonComponent = new ButtonComponent([]()
	{
		ServiceManager::Instance()->getService<PlayerStatsService>().save();
		ServiceManager::Instance()->getService<StateMachine>().popState();
	});

	saveGameButton.addExistingComponent<ButtonComponent>(saveGameButtonComponent);
	saveGameButton.addComponent<TransformComponent>(420, 380, 64, 128, 1);
	saveGameButton.addComponent<ButtonSpriteComponent>("saveGameButton", 1, 3, 0, 1).setStaticAnimation(true);
	saveGameButton.addComponent<CollisionComponent>("saveButton");

	entityManager.addEntityToGroup(saveGameButton, getStateID());
}

void PauseScreenState::createHelpButton() const
{
	auto& helpButton = entityManager.addEntity();
	auto* helpButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("HelpScreen"));
	});

	helpButton.addExistingComponent<ButtonComponent>(helpButtonComponent);
	helpButton.addComponent<TransformComponent>(420, 300, 64, 128, 1);
	helpButton.addComponent<ButtonSpriteComponent>("helpButton", 1, 3, 0, 1).setStaticAnimation(true);

	entityManager.addEntityToGroup(helpButton, getStateID());
}

void PauseScreenState::createExitButton()
{
	auto& exitButton = entityManager.addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		readyForExit = true;
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().changeState(factory.createState("MainMenuState"));
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	exitButton.addComponent<TransformComponent>(420, 460, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("exitButton");

	entityManager.addEntityToGroup(exitButton, getStateID());
}