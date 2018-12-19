#ifndef BOBBERICK_TOOLS_HELPSCREENSTATE_H
#define BOBBERICK_TOOLS_HELPSCREENSTATE_H

#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"

class HelpScreenState : public GameState
{
public:
    HelpScreenState();

    void update() override;
    bool onEnter() override;
    bool onExit() override;
    bool shouldExit() override;

    std::string getStateID() const override;
private:
    bool hasPressedBack;
	SettingsService settings = ServiceManager::Instance()->getService<SettingsService>();
    void makeGui();
    void makeText() const;
    void makeBackground() const;
	void makeGoalText() const;
	void makeHeaderTexts() const;
	void makeMoveTexts() const;
	void makeActivateShieldText() const;
	void makeShootTexts() const;
	void makePauseText() const;
};


#endif //BOBBERICK_TOOLS_HELPSCREENSTATE_H
