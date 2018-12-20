#ifndef BOBBERICK_TOOLS_LEVEL2STATE_H
#define BOBBERICK_TOOLS_LEVEL2STATE_H


#include "../../bobberick-framework/src/GameState.h"

class Level2State : public GameState
{
public:
    void update() override;
    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;

private:
    Entity& makeTileMap() const;
    void makePlayer() const;
};


#endif //BOBBERICK_TOOLS_LEVEL2STATE_H
