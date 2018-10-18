#ifndef BOBBERICK_TOOLS_SPLASHSCREENSTATE_H
#define BOBBERICK_TOOLS_SPLASHSCREENSTATE_H

#include "GameState.h"

class SplashScreenState : public GameState {
	~SplashScreenState();

	void update() override;

	bool onEnter() override;
	bool onExit() override;

	std::string getStateID() const override;
};

#endif //BOBBERICK_TOOLS_SPLASHSCREENSTATE_H