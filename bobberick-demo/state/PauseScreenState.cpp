#include "PauseScreenState.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "StateFactory.h"
#include "../../bobberick-framework/src/StateMachine.h"

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

	return true;
}

bool PauseScreenState::shouldExit()
{
	return readyForExit;
}

bool PauseScreenState::onEnter()
{
	createResumeButton();
	// createSaveButton();
	// createLoadButton();
	createHelpButton();
	createExitButton();

	return true;
}

void PauseScreenState::createResumeButton() const
{
	auto& resumeGameButton = entityManager.addEntity();
	auto* resumeGameButtonComponent = new ButtonComponent([]()
	{
		ServiceManager::Instance()->getService<StateMachine>().popState();
	});

	resumeGameButton.addExistingComponent<ButtonComponent>(resumeGameButtonComponent);
	auto* resumeGameButtonTransformComponent = new TransformComponent();
	resumeGameButtonTransformComponent->position.x = 410;
	resumeGameButtonTransformComponent->position.y = 60;
	resumeGameButtonTransformComponent->height = 64;
	resumeGameButtonTransformComponent->width = 128;
	resumeGameButton.addExistingComponent<TransformComponent>(resumeGameButtonTransformComponent);
	resumeGameButton.addComponent<ButtonSpriteComponent>("resumeGameButton", 1, 3, 0);
	resumeGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	resumeGameButton.addComponent<CollisionComponent>("resumeButton");

	entityManager.addEntityToGroup(resumeGameButton, getStateID());
}

void PauseScreenState::createSaveButton() const
{
	auto& saveGameButton = entityManager.addEntity();
	auto* saveGameButtonComponent = new ButtonComponent([]()
	{
		// TODO: Save the game here.
	});

	saveGameButton.addExistingComponent<ButtonComponent>(saveGameButtonComponent);
	auto* saveGameButtonTransformComponent = new TransformComponent();
	saveGameButtonTransformComponent->position.x = 410;
	saveGameButtonTransformComponent->position.y = 140;
	saveGameButtonTransformComponent->height = 64;
	saveGameButtonTransformComponent->width = 128;
	saveGameButton.addExistingComponent<TransformComponent>(saveGameButtonTransformComponent);
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
	auto* loadGameButtonTransformComponent = new TransformComponent();
	loadGameButtonTransformComponent->position.x = 410;
	loadGameButtonTransformComponent->position.y = 220;
	loadGameButtonTransformComponent->height = 64;
	loadGameButtonTransformComponent->width = 128;
	loadGameButton.addExistingComponent<TransformComponent>(loadGameButtonTransformComponent);
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
	auto* helpButtonTransformComponent = new TransformComponent();
	helpButtonTransformComponent->position.x = 410;
	helpButtonTransformComponent->position.y = 300;
	helpButtonTransformComponent->height = 64;
	helpButtonTransformComponent->width = 128;
	helpButton.addExistingComponent<TransformComponent>(helpButtonTransformComponent);
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
	auto* exitButtonTransformComponent = new TransformComponent();

	exitButtonTransformComponent->position.x = 410;
	exitButtonTransformComponent->position.y = 380;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("exitButton");

	entityManager.addEntityToGroup(exitButton, getStateID());
}