#pragma once
#include "../../bobberick-framework/src/GameState.h"

class CreditScreenState : public GameState
{
public:
	CreditScreenState();
	void update() override;
	bool onEnter() override;
	bool onExit() override;
	bool shouldExit() override;

	std::string getStateID() const override;
private:
	bool readyForExit = false;
	void createText();
	void createExitButton();
	void createBackground();
};
