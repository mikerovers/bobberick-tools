#ifndef BOBBERICK_TOOLS_STATEFACTORY_H
#define BOBBERICK_TOOLS_STATEFACTORY_H

#include <string>
#include "../../bobberick-framework/src/GameState.h"
#include "SplashScreenState.h"
#include "PlayState.h"
#include "MainMenuState.h"

class StateFactory {

public:
	GameState* createState(const std::string type);

private:
	SplashScreenState* createSplashScreenState();
	MainMenuState* createMainMenuState();
	PlayState* createPlayState();
};

#endif //BOBBERICK_TOOLS_STATEFACTORY_H
