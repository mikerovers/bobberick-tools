#ifndef BOBBERICK_TOOLS_STATEFACTORY_H
#define BOBBERICK_TOOLS_STATEFACTORY_H

#include <string>
#include "../../bobberick-framework/src/GameState.h"
#include "SplashScreenState.h"
#include "PlayState.h"
#include "../state/CreditScreenState.h"

class StateFactory {

public:
	GameState* createState(const std::string& type);

private:
	SplashScreenState* createSplashScreenState();
	PlayState* createPlayState();
	CreditScreenState* createCreditScreenState() const;

};

#endif //BOBBERICK_TOOLS_STATEFACTORY_H
