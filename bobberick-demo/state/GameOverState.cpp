#include "GameOverState.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"
#include "../services/PlayerStatsService.h"

std::string GameOverState::getStateID() const
{
	return "gameover";
}

bool GameOverState::onEnter()
{
	makeText();
	makeGui();

	return true;
}

void GameOverState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool GameOverState::onExit()
{
	std::cout << "Exited GameOverState" << std::endl;

	return true;
}

bool GameOverState::shouldExit()
{
	return exitPressed;
}

void GameOverState::makeText() const
{
	makeGameOverText();
	makeXPText();
}

void GameOverState::makeGameOverText() const
{
	auto& gameOverText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	gameOverText.addComponent<TransformComponent>(250, 50, 80, 450, 1);
	gameOverText.addComponent<TextComponent>("defaultLarge", "gameOverText", "Game Over...");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(gameOverText, getStateID());
}

void GameOverState::makeXPText() const
{
	auto& xpGainedText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	xpGainedText.addComponent<TransformComponent>(100, 250, 80, 800, 1);
	xpGainedText.addComponent<TextComponent>("monoMedium", "xpGainedText", "Total XP gained this game: " + std::to_string(ServiceManager::Instance()->getService<PlayerStatsService>().xp));

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(xpGainedText, getStateID());
}

void GameOverState::makeGui()
{
	auto& exitButton = entityManager.addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		exitPressed = true;
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().changeState(factory.createState("MainMenuState"));
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	exitButton.addComponent<TransformComponent>(410, 500, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("button");

	entityManager.addEntityToGroup(exitButton, getStateID());
}