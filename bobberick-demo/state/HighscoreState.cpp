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
	makeHighscoreText();
	updateHighscoreText();

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
		highscores = highscoreService.getScores();
		updateHighscoreText();
	});

	clearButton.addExistingComponent<ButtonComponent>(clearButtonComponent);
	auto* clearButtonTransformComponent = new TransformComponent();
	clearButtonTransformComponent->position.x = 822;
	clearButtonTransformComponent->position.y = 10;
	clearButtonTransformComponent->height = 64;
	clearButtonTransformComponent->width = 128;
	clearButton.addExistingComponent<TransformComponent>(clearButtonTransformComponent);
	clearButton.addComponent<ButtonSpriteComponent>("clearButton", 1,
	                                                   3, 0);
	clearButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

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
	auto* exitButtonTransformComponent = new TransformComponent();

	exitButtonTransformComponent->position.x = 10;
	exitButtonTransformComponent->position.y = 10;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	entityManager.addEntityToGroup(exitButton, getStateID());
}

void HighscoreState::makeHighscoreText() {
	for (int i = 0; i < highscoreTexts.size(); i++) {
		highscoreTexts[i]->addComponent<TransformComponent>(10, 80 + (30 * i), 30, 940, 1);
		highscoreTexts[i]->addComponent<TextComponent>("monoMedium", ("highscore" + std::to_string(i + 1)).c_str(), " ");
	}
}

void HighscoreState::updateHighscoreText() {
	highscores = highscoreService.getScores();
	for (int i = 0; i < highscores.size(); i++) {
		highscoreTexts[i]->getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(i + 1), 2, true) + ". " + textFormatter.addSpaces(std::to_string(highscores[i]), 40, true) + " XP");
	}
}
