#include <string>
#include "HighscoreState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include <iostream>
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"

std::string HighscoreState::getStateID() const
{
	return "highscores";
}

void HighscoreState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool HighscoreState::onEnter()
{
	for (const auto& system : systems)
	{
		system->init();
	}

	std::cout << "Entered HighscoreState" << std::endl;

	makeClearButton();
	makeExitButton();
	makeTitleText();
	makeHighscoreText();
	updateHighscoreText();
	makeBackground();

	return true;
}

bool HighscoreState::onExit()
{
	std::cout << "Exited HighscoreState" << std::endl;
	return true;
}

bool HighscoreState::shouldExit()
{
	return readyForExit;
}

void HighscoreState::makeClearButton()
{
	auto& clearButton = entityManager.addEntity();
	auto* clearButtonComponent = new ButtonComponent([this]()
	{
		highscoreService.resetScores();
		highscores = highscoreService.getScores();
		updateHighscoreText();
	});

	clearButton.addExistingComponent<ButtonComponent>(clearButtonComponent);
	clearButton.addComponent<TransformComponent>(822, 10, 64, 128, 1);
	clearButton.addComponent<ButtonSpriteComponent>("clearButton", 1, 3, 0, 1).setStaticAnimation(true);
	
	entityManager.addEntityToGroup(clearButton, getStateID());
}

void HighscoreState::makeExitButton()
{
	auto& exitButton = entityManager.addEntity();
	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		readyForExit = true;
		std::cout << "Exit button clicked" << std::endl;
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	exitButton.addComponent<TransformComponent>(10, 10, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);

	entityManager.addEntityToGroup(exitButton, getStateID());
}

void HighscoreState::makeTitleText() {
	auto& title = entityManager.addEntity();
	entityManager.addEntityToGroup(title, getStateID());
	title.addComponent<TransformComponent>(300, 100, 64, 360, 1);
	title.addComponent<TextComponent>("defaultLarge", "scoresTitle", "Hall of Fame");
}

void HighscoreState::makeHighscoreText() {
	for (int i = 0; i < highscoreTexts.size(); i++) {
		highscoreTexts[i]->addComponent<TransformComponent>(320, 180 + (30 * i), 30, 320, 1);
		highscoreTexts[i]->addComponent<TextComponent>("monoMedium", ("highscore" + std::to_string(i + 1)).c_str(), " ");
	}
}

void HighscoreState::updateHighscoreText() {
	highscores = highscoreService.getScores();
	for (int i = 0; i < highscoreTexts.size(); i++) {
		highscoreTexts[i]->getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(i + 1), 2, true) + ". " + textFormatter.addSpaces(std::to_string(highscores[i]), 10, true) + " XP");
	}
}

void HighscoreState::makeBackground()
{
	auto& background = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	background.addComponent<TransformComponent>(0, 0, 704, 960, 1);
	background.addComponent<SpriteComponent>("menuBackground", 0);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(background, getStateID());
}
