#ifndef BOBBERICK_TOOLS_STATEMACHINE_H
#define BOBBERICK_TOOLS_STATEMACHINE_H

#include <vector>
#include "GameState.h"

class StateMachine : public Service
{
public:
    void init() override;
    void clean() override;
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    GameState* peekState();

    void update();
private:
    std::vector<GameState*> gameStates;
};


#endif //BOBBERICK_TOOLS_STATEMACHINE_H
