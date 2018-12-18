#include "CreditScreenState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"

CreditScreenState::CreditScreenState() = default;

void CreditScreenState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool CreditScreenState::onEnter()
{
	createText();
	createExitButton();
	return true;
}

void CreditScreenState::createText() {
	auto &entityManager = ServiceManager::Instance()->getService<EntityManager>();
	auto& titleText = entityManager.addEntity();
	titleText.addComponent<TransformComponent>(390, 10, 80, 180, 1);
	titleText.addComponent<TextComponent>("defaultLarge", "creditsTitle", "Credits");
	entityManager.addEntityToGroup(titleText, getStateID());

	auto& devTeamText = entityManager.addEntity();
	devTeamText.addComponent<TransformComponent>(230, 120, 80, 510, 1);
	devTeamText.addComponent<TextComponent>("defaultLarge", "creditsDevTeam", "Development Team");
	entityManager.addEntityToGroup(devTeamText, getStateID());

	auto& wouterText = entityManager.addEntity();
	wouterText.addComponent<TransformComponent>(360, 210, 45, 250, 1);
	wouterText.addComponent<TextComponent>("defaultMedium", "creditsWouter", "Wouter Bouwman");
	entityManager.addEntityToGroup(wouterText, getStateID());

	auto& thimText = entityManager.addEntity();
	thimText.addComponent<TransformComponent>(397, 260, 45, 175, 1);
	thimText.addComponent<TextComponent>("defaultMedium", "creditsThim", "Thim Heider");
	entityManager.addEntityToGroup(thimText, getStateID());

	auto& kevinText = entityManager.addEntity();
	kevinText.addComponent<TransformComponent>(360, 310, 45, 250, 1);
	kevinText.addComponent<TextComponent>("defaultMedium", "creditsKevin", "Kevin van Rossum");
	entityManager.addEntityToGroup(kevinText, getStateID());

	auto& mikeText = entityManager.addEntity();
	mikeText.addComponent<TransformComponent>(400, 360, 45, 170, 1);
	mikeText.addComponent<TextComponent>("defaultMedium", "creditsMike", "Mike Rovers");
	entityManager.addEntityToGroup(mikeText, getStateID());

	auto& roelText = entityManager.addEntity();
	roelText.addComponent<TransformComponent>(396, 410, 45, 178, 1);
	roelText.addComponent<TextComponent>("defaultMedium", "creditsRoel", "Roel Wolters");
	entityManager.addEntityToGroup(roelText, getStateID());

	auto& mascotText = entityManager.addEntity();
	mascotText.addComponent<TransformComponent>(390, 490, 80, 190, 1);
	mascotText.addComponent<TextComponent>("defaultLarge", "creditsMascot", "Mascot");
	entityManager.addEntityToGroup(mascotText, getStateID());

	auto& joostText = entityManager.addEntity();
	joostText.addComponent<TransformComponent>(383, 580, 45, 205, 1);
	joostText.addComponent<TextComponent>("defaultMedium", "creditsJoost", "Joost de Bruijn");
	entityManager.addEntityToGroup(joostText, getStateID());
}

void CreditScreenState::createExitButton() {
	auto &entityManager = ServiceManager::Instance()->getService<EntityManager>();
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

bool CreditScreenState::onExit()
{
	return true;
}

bool CreditScreenState::shouldExit()
{
	return readyForExit;
}

std::string CreditScreenState::getStateID() const
{
	return "creditsScreen";
}
