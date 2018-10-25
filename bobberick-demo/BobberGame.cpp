#include "BobberGame.h"

bool BobberGame::setup()
{
	if (Game::setup()) {
		stateFactory = std::make_shared<StateFactory>();
		stateMachine->pushState(stateFactory->createState("SplashScreenState"));
		return true;
	} else {
		return false;
	}
}

void BobberGame::start()
{
    Game::start();
}
