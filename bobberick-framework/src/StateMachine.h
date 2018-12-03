#ifndef BOBBERICK_TOOLS_STATEMACHINE_H
#define BOBBERICK_TOOLS_STATEMACHINE_H

#include <vector>
#include "GameState.h"

class StateMachine : public Service
{
public:
    void init() override;
    void clean() override;
    void pushState(std::unique_ptr<GameState> pState);
    void changeState(std::unique_ptr<GameState> pState);
    void popState();
    GameState& peekState();
	bool isEmpty() const;

    void update();
private:
    std::vector<std::unique_ptr<GameState>> gameStates;
};


#endif //BOBBERICK_TOOLS_STATEMACHINE_H
