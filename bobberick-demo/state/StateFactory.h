#ifndef BOBBERICK_TOOLS_STATEFACTORY_H
#define BOBBERICK_TOOLS_STATEFACTORY_H

#include <string>
#include "../../bobberick-framework/src/GameState.h"
#include "SplashScreenState.h"
#include "Level1State.h"
#include "MainMenuState.h"
#include "../state/CreditScreenState.h"
#include "HelpScreenState.h"
#include "EndScreenState.h"
#include "Level2State.h"
#include "Level3State.h"
#include "PauseScreenState.h"
#include "SkillScreenState.h"
#include "SettingsScreenState.h"

class StateFactory {

public:
	GameState* createState(const std::string& type);

private:
	SplashScreenState* createSplashScreenState();
	Level1State* createPlayState();
	Level2State* createLevel2State() const;
    Level3State* createLevel3State() const;
	MainMenuState* createMainMenuState();
	CreditScreenState* createCreditScreenState() const;
	HelpScreenState* createHelpScreenState() const;
    EndScreenState* createEndScreenState() const;
    PauseScreenState* createPauseScreenState() const;
	SkillScreenState* createSkillScreenState() const;
	SettingsScreenState* createSettingsScreenState() const;
};

#endif //BOBBERICK_TOOLS_STATEFACTORY_H
