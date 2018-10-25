#ifndef BOBBERICK_TOOLS_STATEMACHINE_H
#define BOBBERICK_TOOLS_STATEMACHINE_H


#include <vector>
#include "GameState.h"

class StateMachine {
public:
    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();
    GameState* peekState();

    void update();
private:
    std::vector<GameState*> gameStates;
};


#endif //BOBBERICK_TOOLS_STATEMACHINE_H
