#ifndef BOBBERICK_TOOLS_MAINMENUSTATE_H
#define BOBBERICK_TOOLS_MAINMENUSTATE_H
#include "../../bobberick-framework/src/GameState.h"

class MainMenuState : public GameState
{
public:
	bool onEnter() override;
	bool onExit() override;
	void update() override;
	std::string getStateID() const override;
	bool shouldExit() override;

private:
	bool _playGamePressed = false;
	Entity* entities[4] = {};
	// Entity* buttons[3] = {};
	// Entity* player;
	// Entity* orc;
	// Entity* zombie;
	// Entity* fireWizard;

	void createAnimatedBackground();

	void makeStartGameButton();
	void makeOptionsButton();
	void makeExitButton();

	void determineMovementDirection();
};

#endif // BOBBERICK_TOOLS_MAINMENUSTATE_H