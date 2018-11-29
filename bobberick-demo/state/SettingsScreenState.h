#ifndef BOBBERICK_TOOLS_SETTINGSSCREENSTATE_H
#define BOBBERICK_TOOLS_SETTINGSSCREENSTATE_H

#include "../../bobberick-framework/src/GameState.h"

class SettingsScreenState : public GameState
{
public:
	SettingsScreenState();

    void update() override;
    bool onEnter() override;
    bool onExit() override;
    bool shouldExit() override;

    std::string getStateID() const override;
private:
    bool hasPressedBack;
	void createTexts() const;
	void createSettingsText() const;
	void createMusicToggleButton() const;
	void createExitButton();
};


#endif //BOBBERICK_TOOLS_SETTINGSSCREENSTATE_H