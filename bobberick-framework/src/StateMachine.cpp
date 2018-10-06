#include "StateMachine.h"

void StateMachine::pushState(GameState *pState)
{
    gameStates.push_back(pState);
    gameStates.back()->onEnter();
}

void StateMachine::popState()
{
    if (!gameStates.empty()) {
        if (gameStates.back()->onExit()) {
            delete gameStates.back();
            gameStates.pop_back();
        }
    }
}

void StateMachine::changeState(GameState *pState)
{
    if (!gameStates.empty()) {
        if (gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }

        if (gameStates.back()->onExit()) {
            delete gameStates.back();
            gameStates.pop_back();
        }
    }

    gameStates.push_back(pState);

    gameStates.back()->onEnter();
}

void StateMachine::update() {
    if (!gameStates.empty()) {
        gameStates.back()->update();
    }
}
