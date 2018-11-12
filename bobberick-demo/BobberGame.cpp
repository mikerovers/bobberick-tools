#include "BobberGame.h"
#include "state/PlayState.h"

bool BobberGame::setup()
{
	if (Game::setup()) {
		stateFactory = std::make_shared<StateFactory>();

		getStateMachine()->pushState(stateFactory->createState("PlayState"));
		//getStateMachine()->pushState(stateFactory->createState("SplashScreenState"));
        getStateMachine()->peekState()->onEnter();
		//getStateMachine()->pushState(stateFactory->createState("TestState"));
		//getStateMachine()->peekState()->onEnter();

		return true;
	} else {
		return false;
	}
}

void BobberGame::start()
{
    Game::start();
}
