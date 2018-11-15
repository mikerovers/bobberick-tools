#ifndef BOBBERICK_TOOLS_TESTSTATE_H
#define BOBBERICK_TOOLS_TESTSTATE_H

#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../../bobberick-framework/src/GameState.h"

class TestState : public GameState
{
    void update() override;
    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;
};

#endif //BOBBERICK_TOOLS_TESTSTATE_H
