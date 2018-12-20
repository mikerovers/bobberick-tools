#ifndef BOBBERICK_TOOLS_ENDSCREENSTATE_H
#define BOBBERICK_TOOLS_ENDSCREENSTATE_H

#include "../../bobberick-framework/src/GameState.h"

class EndScreenState : public GameState
{
public:
    bool onEnter() override;
    bool onExit() override;
    void update() override;
    bool shouldExit() override;
    std::string getStateID() const override;

private:
    bool readyForExit = false;
    void makeExitButton();
    void makeText() const;
    void makeBackground() const;
};


#endif //BOBBERICK_TOOLS_ENDSCREENSTATE_H
