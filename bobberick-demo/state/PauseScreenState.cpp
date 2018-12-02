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
	pauseText.addComponent<TransformComponent>(235, 50, 80, 450, 1);
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
	resumeGameButton.addComponent<TransformComponent>(410, 160, 64, 128, 1);
	resumeGameButton.addComponent<ButtonSpriteComponent>("resumeGameButton", 1, 3, 0);
	resumeGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
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
	auto* optionsButtonTransformComponent = new TransformComponent();
	optionsButtonTransformComponent->position.x = 410;
	optionsButtonTransformComponent->position.y = 240;
	optionsButtonTransformComponent->height = 64;
	optionsButtonTransformComponent->width = 128;
	optionsButton.addExistingComponent<TransformComponent>(optionsButtonTransformComponent);
	optionsButton.addComponent<ButtonSpriteComponent>("optionsButton", 1, 3, 0);
	optionsButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
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
	saveGameButton.addComponent<TransformComponent>(410, 320, 64, 128, 1);
	saveGameButton.addComponent<ButtonSpriteComponent>("saveGameButton", 1, 3, 0);
	saveGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	saveGameButton.addComponent<CollisionComponent>("saveButton");

	entityManager.addEntityToGroup(saveGameButton, getStateID());
}

void PauseScreenState::createLoadButton() const
{
	auto& loadGameButton = entityManager.addEntity();
	auto* loadGameButtonComponent = new ButtonComponent([]()
	{
		// TODO: Load a saved game here.
	});

	loadGameButton.addExistingComponent<ButtonComponent>(loadGameButtonComponent);
	loadGameButton.addComponent<TransformComponent>(410, 320, 64, 128, 1);
	loadGameButton.addComponent<ButtonSpriteComponent>("loadGameButton", 1, 3, 0);
	loadGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	loadGameButton.addComponent<CollisionComponent>("loadButton");

	entityManager.addEntityToGroup(loadGameButton, getStateID());
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
	helpButton.addComponent<TransformComponent>(410, 400, 64, 128, 1);
	helpButton.addComponent<ButtonSpriteComponent>("helpButton", 1, 3, 0);
	helpButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

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
	exitButton.addComponent<TransformComponent>(410, 480, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("exitButton");

	entityManager.addEntityToGroup(exitButton, getStateID());
}