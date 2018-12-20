#ifndef BOBBERICK_TOOLS_STATEFACTORY_H
#define BOBBERICK_TOOLS_STATEFACTORY_H

#include <string>
#include "../../bobberick-framework/src/GameState.h"
#include "SplashScreenState.h"
#include "Level1State.h"
#include "MainMenuState.h"
#include "CreditScreenState.h"
#include "HelpScreenState.h"
#include "EndScreenState.h"
#include "Level2State.h"
#include "Level3State.h"
#include "PauseScreenState.h"
#include "SkillScreenState.h"
#include "SettingsScreenState.h"
#include "HighscoreState.h"
#include "GameOverState.h"
#include "Level4State.h"
#include "KeyMappingState.h"

class StateFactory {

public:
	std::unique_ptr<GameState> createState(const std::string& type);

private:
	std::unique_ptr<SplashScreenState> createSplashScreenState();
	std::unique_ptr<Level1State> createPlayState();
	std::unique_ptr<Level2State> createLevel2State() const;
	std::unique_ptr<Level3State> createLevel3State() const;
	std::unique_ptr<Level4State> createLevel4State() const;
	std::unique_ptr<MainMenuState> createMainMenuState();
	std::unique_ptr<CreditScreenState> createCreditScreenState() const;
	std::unique_ptr<HighscoreState> createHighscoreState() const;
	std::unique_ptr<HelpScreenState> createHelpScreenState() const;
	std::unique_ptr<EndScreenState> createEndScreenState() const;
	std::unique_ptr<PauseScreenState> createPauseScreenState() const;
	std::unique_ptr<SkillScreenState> createSkillScreenState() const;
	std::unique_ptr<SettingsScreenState> createSettingsScreenState() const;
	std::unique_ptr<GameOverState> createGameOverState() const;
	std::unique_ptr<KeyMappingState> createKeyMappingState() const;
};

#endif //BOBBERICK_TOOLS_STATEFACTORY_H
