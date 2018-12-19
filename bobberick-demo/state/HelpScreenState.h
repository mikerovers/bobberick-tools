#ifndef BOBBERICK_TOOLS_HELPSCREENSTATE_H
#define BOBBERICK_TOOLS_HELPSCREENSTATE_H

#include "../../bobberick-framework/src/GameState.h"

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
    void makeGui();
    void makeText() const;
    void makeBackground() const;
};


#endif //BOBBERICK_TOOLS_HELPSCREENSTATE_H
