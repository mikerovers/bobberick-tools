#include "GameOverState.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"
#include "../services/PlayerStatsService.h"
#include "../services/HighscoreService.h"

std::string GameOverState::getStateID() const
{
	return "gameover";
}

bool GameOverState::onEnter()
{
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	highscorePos = ServiceManager::Instance()->getService<HighscoreService>().saveScore(playerStats.xp);

	makeText();
	makeGui();
	makeBackground();

	playerStats.init();

	return true;
}

void GameOverState::update()
{
	for (const auto& system : systems)
	{
		if (exiting)
			break;

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
	makeHighscoreText();
}

void GameOverState::makeGameOverText() const
{
	auto& gameOverText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	gameOverText.addComponent<TransformComponent>(250, 70, 80, 450, 1);
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

void GameOverState::makeHighscoreText() const
{
	auto& highscoreText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	highscoreText.addComponent<TransformComponent>(100, 350, 80, 800, 1);
	if (highscorePos > 0) {
		highscoreText.addComponent<TextComponent>("monoMedium", "highscoreText", "New highscore at position: " + std::to_string(highscorePos));
	}

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(highscoreText, getStateID());
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
	exitButton.addComponent<TransformComponent>(10, 10, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);
	exitButton.addComponent<CollisionComponent>("button");

	entityManager.addEntityToGroup(exitButton, getStateID());
}

void GameOverState::makeBackground() const
{
	auto& background = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	background.addComponent<TransformComponent>(0, 0, 704, 960, 1);
	background.addComponent<SpriteComponent>("menuBackground", 0);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(background, getStateID());
}
