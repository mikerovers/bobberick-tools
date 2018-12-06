#include <string>
#include "SkillScreenState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../services/PlayerStatsService.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
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

	makeStartGameButton();
	makeHpButton();
	makeAtButton();
	makeDfButton();
	makeShdTimeButton();
	makeShdRecovButton();
	makeExitButton();

	makeHpText();
	makeAtText();
	makeDfText();
	makeShdTimeText();
	makeShdRecovText();

	PlayerStatsService& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	playerStats.init();
	updateHpText(playerStats);
	updateAtText(playerStats);
	updateDfText(playerStats);
	updateShdTimeText(playerStats);
	updateShdRecovText(playerStats);

	xpImage.addComponent<TransformComponent>(10, 1, 48, 48, 1);
	xpImage.addComponent<SpriteComponent>("hudXp", true);
	xpText.addComponent<TransformComponent>(60, 10, 30, 270, 1);
	xpText.addComponent<TextComponent>("monoMedium", "xpText", textFormatter.addSpaces(std::to_string(playerStats.getXPtotal()), 15, false));

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

void SkillScreenState::makeStartGameButton() const
{
	auto& playGameButton = entityManager.addEntity();
	auto* playGameButtonComponent = new ButtonComponent([]()
	{
		StateFactory factory{};
		ServiceManager::Instance()->getService<StateMachine>().pushState(factory.createState("Level2State"));
	});

	playGameButton.addExistingComponent<ButtonComponent>(playGameButtonComponent);
	playGameButton.addComponent<TransformComponent>(550, 60, 64, 128, 1);
	playGameButton.addComponent<ButtonSpriteComponent>("startGameButton", 1,
	                                                   3, 0);
	playGameButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	entityManager.addEntityToGroup(playGameButton, getStateID());
}

void SkillScreenState::makeHpButton()
{
	auto& hpButton = entityManager.addEntity();
	auto* hpButtonComponent = new ButtonComponent([this]()
	{
		PlayerStatsService& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
		playerStats.upgradeHPlevel();
		xpText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.getXPtotal()), 15, false));
		updateHpText(playerStats);
	});

	hpButton.addExistingComponent<ButtonComponent>(hpButtonComponent);
	hpButton.addComponent<TransformComponent>(420, 140, 64, 128, 1);
	hpButton.addComponent<ButtonSpriteComponent>("healthButton", 1, 3, 0);
	hpButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(hpButton, getStateID());
}

void SkillScreenState::makeAtButton()
{
	auto& atButton = entityManager.addEntity();
	auto* atButtonComponent = new ButtonComponent([this]()
	{
		PlayerStatsService& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
		playerStats.upgradeATlevel();
		xpText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.getXPtotal()), 15, false));
		updateAtText(playerStats);
	});

	atButton.addExistingComponent<ButtonComponent>(atButtonComponent);
	atButton.addComponent<TransformComponent>(420, 220, 64, 128, 1);
	atButton.addComponent<ButtonSpriteComponent>("attackButton", 1, 3, 0);
	atButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(atButton, getStateID());
}

void SkillScreenState::makeDfButton()
{
	auto& dfButton = entityManager.addEntity();
	auto* dfButtonComponent = new ButtonComponent([this]()
	{
		PlayerStatsService& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
		playerStats.upgradeDFlevel();
		xpText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.getXPtotal()), 15, false));
		updateDfText(playerStats);
	});

	dfButton.addExistingComponent<ButtonComponent>(dfButtonComponent);
	dfButton.addComponent<TransformComponent>(420, 300, 64, 128, 1);
	dfButton.addComponent<ButtonSpriteComponent>("defenseButton", 1, 3, 0);
	dfButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(dfButton, getStateID());
}

void SkillScreenState::makeShdTimeButton()
{
	auto& shdTimeButton = entityManager.addEntity();
	auto* shdTimeButtonComponent = new ButtonComponent([this]()
	{
		PlayerStatsService& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
		playerStats.upgradeSHDlevel();
		xpText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.getXPtotal()), 15, false));
		updateShdTimeText(playerStats);
	});

	shdTimeButton.addExistingComponent<ButtonComponent>(shdTimeButtonComponent);
	shdTimeButton.addComponent<TransformComponent>(420, 380, 64, 128, 1);
	shdTimeButton.addComponent<ButtonSpriteComponent>("shieldButton", 1, 3, 0);
	shdTimeButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(shdTimeButton, getStateID());
}

void SkillScreenState::makeShdRecovButton()
{
	auto& shdRecovButton = entityManager.addEntity();
	auto* shdRecovButtonComponent = new ButtonComponent([this]()
	{
		PlayerStatsService& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
		playerStats.upgradeSHDrecovLevel();
		xpText.getComponent<TextComponent>().setText(textFormatter.addSpaces(std::to_string(playerStats.getXPtotal()), 15, false));
		updateShdRecovText(playerStats);
	});

	shdRecovButton.addExistingComponent<ButtonComponent>(shdRecovButtonComponent);
	shdRecovButton.addComponent<TransformComponent>(420, 460, 64, 128, 1);
	shdRecovButton.addComponent<ButtonSpriteComponent>("recoveryButton", 1, 3, 0);
	shdRecovButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
	entityManager.addEntityToGroup(shdRecovButton, getStateID());
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
	exitButton.addComponent<TransformComponent>(290, 90, 64, 128, 1);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	entityManager.addEntityToGroup(exitButton, getStateID());
}

void SkillScreenState::makeHpText() const
{
	hpCost.addComponent<TransformComponent>(145, 170, 30, 270, 1);
	hpCost.addComponent<TextComponent>("monoMedium", "hpCost", " ");
	hpLevel.addComponent<TransformComponent>(145, 140, 30, 270, 1);
	hpLevel.addComponent<TextComponent>("monoMedium", "hpLevel", " ");
	hpValue.addComponent<TransformComponent>(555, 140, 30, 270, 1);
	hpValue.addComponent<TextComponent>("monoMedium", "hpValue", " ");
	hpNext.addComponent<TransformComponent>(555, 170, 30, 270, 1);
	hpNext.addComponent<TextComponent>("monoMedium", "hpNext", " ");
}

void SkillScreenState::makeAtText() const
{
	atCost.addComponent<TransformComponent>(145, 250, 30, 270, 1);
	atCost.addComponent<TextComponent>("monoMedium", "atCost", " ");
	atLevel.addComponent<TransformComponent>(145, 220, 30, 270, 1);
	atLevel.addComponent<TextComponent>("monoMedium", "atLevel", " ");
	atValue.addComponent<TransformComponent>(555, 220, 30, 270, 1);
	atValue.addComponent<TextComponent>("monoMedium", "atValue", " ");
	atNext.addComponent<TransformComponent>(555, 250, 30, 270, 1);
	atNext.addComponent<TextComponent>("monoMedium", "atNext", " ");
}

void SkillScreenState::makeDfText() const
{
	dfCost.addComponent<TransformComponent>(145, 330, 30, 270, 1);
	dfCost.addComponent<TextComponent>("monoMedium", "dfCost", " ");
	dfLevel.addComponent<TransformComponent>(145, 300, 30, 270, 1);
	dfLevel.addComponent<TextComponent>("monoMedium", "dfLevel", " ");
	dfValue.addComponent<TransformComponent>(555, 300, 30, 270, 1);
	dfValue.addComponent<TextComponent>("monoMedium", "dfValue", " ");
	dfNext.addComponent<TransformComponent>(555, 330, 30, 270, 1);
	dfNext.addComponent<TextComponent>("monoMedium", "dfNext", " ");
}

void SkillScreenState::makeShdTimeText() const
{
	shdTimeCost.addComponent<TransformComponent>(145, 410, 30, 270, 1);
	shdTimeCost.addComponent<TextComponent>("monoMedium", "shdTimeCost", " ");
	shdTimeLevel.addComponent<TransformComponent>(145, 380, 30, 270, 1);
	shdTimeLevel.addComponent<TextComponent>("monoMedium", "shdTimeLevel", " ");
	shdTimeValue.addComponent<TransformComponent>(555, 380, 30, 270, 1);
	shdTimeValue.addComponent<TextComponent>("monoMedium", "shdTimeValue", " ");
	shdTimeNext.addComponent<TransformComponent>(555, 410, 30, 270, 1);
	shdTimeNext.addComponent<TextComponent>("monoMedium", "shdTimeNext", " ");
}

void SkillScreenState::makeShdRecovText() const
{
	shdRecovCost.addComponent<TransformComponent>(145, 490, 30, 270, 1);
	shdRecovCost.addComponent<TextComponent>("monoMedium", "shdRecovCost", " ");
	shdRecovLevel.addComponent<TransformComponent>(145, 460, 30, 270, 1);
	shdRecovLevel.addComponent<TextComponent>("monoMedium", "shdRecovLevel", " ");
	shdRecovValue.addComponent<TransformComponent>(555, 460, 30, 270, 1);
	shdRecovValue.addComponent<TextComponent>("monoMedium", "shdRecovValue", " ");
	shdRecovNext.addComponent<TransformComponent>(555, 490, 30, 270, 1);
	shdRecovNext.addComponent<TextComponent>("monoMedium", "shdRecovNext", " ");
}

void SkillScreenState::updateHpText(PlayerStatsService& playerStats) {
	hpLevel.getComponent<TextComponent>().setText(textFormatter.addSpaces("Level: " + std::to_string(playerStats.getHPlevel()), 15, true));
	hpValue.getComponent<TextComponent>().setText(textFormatter.addSpaces("Value: " + std::to_string(playerStats.getHPvalue(false)), 15, false));
	if (playerStats.getHPcost() > -1) {
		hpCost.getComponent<TextComponent>().setText(textFormatter.addSpaces("Cost: " + std::to_string(playerStats.getHPcost()), 15, true));
		hpNext.getComponent<TextComponent>().setText(textFormatter.addSpaces("Next: " + std::to_string(playerStats.getHPvalue(true)), 15, false));
	} else {
		hpCost.getComponent<TextComponent>().setText(" ");
		hpNext.getComponent<TextComponent>().setText(" ");
	}

}

void SkillScreenState::updateAtText(PlayerStatsService& playerStats) {
	atLevel.getComponent<TextComponent>().setText(textFormatter.addSpaces("Level: " + std::to_string(playerStats.getATlevel()), 15, true));
	atValue.getComponent<TextComponent>().setText(textFormatter.addSpaces("Value: " + std::to_string(playerStats.getATminValue(false)) + "-" + std::to_string(playerStats.getATmaxValue(false)), 15, false));
	if (playerStats.getATcost() > -1) {
		atCost.getComponent<TextComponent>().setText(textFormatter.addSpaces("Cost: " + std::to_string(playerStats.getATcost()), 15, true));
		atNext.getComponent<TextComponent>().setText(textFormatter.addSpaces("Next: " + std::to_string(playerStats.getATminValue(true)) + "-" + std::to_string(playerStats.getATmaxValue(true)), 15, false));
	} else {
		atCost.getComponent<TextComponent>().setText(" ");
		atNext.getComponent<TextComponent>().setText(" ");
	}
}

void SkillScreenState::updateDfText(PlayerStatsService& playerStats) {
	dfLevel.getComponent<TextComponent>().setText(textFormatter.addSpaces("Level: " + std::to_string(playerStats.getDFlevel()), 15, true));
	dfValue.getComponent<TextComponent>().setText(textFormatter.addSpaces("Value: " + std::to_string(playerStats.getDFvalue(false)), 15, false));
	if (playerStats.getDFcost() > -1) {
		dfCost.getComponent<TextComponent>().setText(textFormatter.addSpaces("Cost: " + std::to_string(playerStats.getDFcost()), 15, true));
		dfNext.getComponent<TextComponent>().setText(textFormatter.addSpaces("Next: " + std::to_string(playerStats.getDFvalue(true)), 15, false));
	} else {
		dfCost.getComponent<TextComponent>().setText(" ");
		dfNext.getComponent<TextComponent>().setText(" ");
	}
}

void SkillScreenState::updateShdTimeText(PlayerStatsService& playerStats) {
	shdTimeLevel.getComponent<TextComponent>().setText(textFormatter.addSpaces("Level: " + std::to_string(playerStats.getSHDlevel()), 15, true));
	shdTimeValue.getComponent<TextComponent>().setText(textFormatter.addSpaces("Value: " + std::to_string(playerStats.getSHDvalue(false)), 15, false));
	if (playerStats.getSHDcost() > -1) {
		shdTimeCost.getComponent<TextComponent>().setText(textFormatter.addSpaces("Cost: " + std::to_string(playerStats.getSHDcost()), 15, true));
		shdTimeNext.getComponent<TextComponent>().setText(textFormatter.addSpaces("Next: " + std::to_string(playerStats.getSHDvalue(true)), 15, false));
	} else {
		shdTimeCost.getComponent<TextComponent>().setText(" ");
		shdTimeNext.getComponent<TextComponent>().setText(" ");
	}
}

void SkillScreenState::updateShdRecovText(PlayerStatsService& playerStats) {
	shdRecovLevel.getComponent<TextComponent>().setText(textFormatter.addSpaces("Level: " + std::to_string(playerStats.getSHDrecovLevel()), 15, true));
	shdRecovValue.getComponent<TextComponent>().setText(textFormatter.addSpaces("Value: " + std::to_string(playerStats.getSHDrecovValue(false)).substr(0, 4), 15, false));
	if (playerStats.getSHDrecovCost() > -1) {
		shdRecovCost.getComponent<TextComponent>().setText(textFormatter.addSpaces("Cost: " + std::to_string(playerStats.getSHDrecovCost()), 15, true));
		shdRecovNext.getComponent<TextComponent>().setText(textFormatter.addSpaces("Next: " + std::to_string(playerStats.getSHDrecovValue(true)).substr(0, 4), 15, false));
	} else {
		shdRecovCost.getComponent<TextComponent>().setText(" ");
		shdRecovNext.getComponent<TextComponent>().setText(" ");
	}
}

