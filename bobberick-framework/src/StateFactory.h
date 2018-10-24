#ifndef BOBBERICK_TOOLS_STATEFACTORY_H
#define BOBBERICK_TOOLS_STATEFACTORY_H

#include <string>
#include "GameState.h"
#include "SplashScreenState.h"

class StateFactory {

public:
	GameState* createState(const std::string& type) const;

private:
	SplashScreenState* createSplashScreenState() const;
    GameState* createCreditScreenState() const;

};

#endif //BOBBERICK_TOOLS_STATEFACTORY_H
