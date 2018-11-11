#ifndef BOBBERICK_TOOLS_MAINMENUSTATE_H
#define BOBBERICK_TOOLS_MAINMENUSTATE_H

#include "../../bobberick-framework/src/GameState.h"

class MainMenuState : public GameState
{
public:
	void update() override;
	bool onEnter() override;
	bool onExit() override;

	bool shouldExit() override;

	std::string getStateID() const override;

private:
	bool _playGamePressed = false;

	void makeStartGameButton();
	void makeExitButton();
};

#endif //BOBBERICK_TOOLS_MAINMENUSTATE_H