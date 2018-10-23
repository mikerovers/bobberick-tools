#ifndef BOBBERICK_TOOLS_SPLASHSCREENSTATE_H
#define BOBBERICK_TOOLS_SPLASHSCREENSTATE_H

#include "GameState.h"

class SplashScreenState : public GameState {
public:
	SplashScreenState() {};
	~SplashScreenState();

	void update() override;

	bool onEnter() override;
	bool onExit() override;

	bool shouldExit() override;

	std::vector<std::shared_ptr<Entity>> fadeEntities;

	std::string getStateID() const override;
};

#endif //BOBBERICK_TOOLS_SPLASHSCREENSTATE_H