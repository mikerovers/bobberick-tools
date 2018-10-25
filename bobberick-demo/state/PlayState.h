#ifndef BOBBERICK_TOOLS_PLAYSTATE_H
#define BOBBERICK_TOOLS_PLAYSTATE_H

#include "../../bobberick-framework/src/GameState.h"

class PlayState : public GameState
{
public:
    void update() override;
    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;
};


#endif //BOBBERICK_TOOLS_PLAYSTATE_H
