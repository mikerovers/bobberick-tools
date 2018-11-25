#ifndef BOBBERICK_TOOLS_LEVEL3STATE_H
#define BOBBERICK_TOOLS_LEVEL3STATE_H


#include "../../bobberick-framework/src/GameState.h"

class Level3State : public GameState
{
public:
    void update() override;
    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;

private:
    Entity& makeTileMap() const;
    void makeEnemies() const;
    void makePlayer() const;
};


#endif //BOBBERICK_TOOLS_LEVEL3STATE_H
