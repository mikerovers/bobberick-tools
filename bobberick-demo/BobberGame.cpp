#include "BobberGame.h"
#include "state/PlayState.h"

bool BobberGame::setup()
{
    Game::setup();

    stateMachine->pushState(new PlayState());

    return true;
}

void BobberGame::start()
{
    Game::start();
}
