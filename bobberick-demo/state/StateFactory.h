#ifndef BOBBERICK_TOOLS_STATEFACTORY_H
#define BOBBERICK_TOOLS_STATEFACTORY_H

#include <string>
#include "../../bobberick-framework/src/GameState.h"
#include "SplashScreenState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "../state/CreditScreenState.h"
#include "HelpScreenState.h"
#include "EndScreenState.h"

class StateFactory {

public:
	GameState* createState(const std::string& type);

private:
	SplashScreenState* createSplashScreenState();
	PlayState* createPlayState();
	MainMenuState* createMainMenuState();
	CreditScreenState* createCreditScreenState() const;
	HelpScreenState* createHelpScreenState() const;
    EndScreenState* createEndScreenState() const;
};

#endif //BOBBERICK_TOOLS_STATEFACTORY_H
