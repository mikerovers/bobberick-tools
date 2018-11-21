#include "BobberGame.h"
#include "state/PlayState.h"

bool BobberGame::setup()
{
	if (Game::setup()) {
		stateFactory = std::make_shared<StateFactory>();

		ServiceManager::Instance()->getService<StateMachine>().pushState(stateFactory->createState("MainMenuState"));
		//getStateMachine()->pushState(stateFactory->createState("MainMenuState"));
		//getStateMachine()->pushState(stateFactory->createState("SplashScreenState"));
        //getStateMachine()->peekState()->onEnter();
		//getStateMachine()->pushState(stateFactory->createState("TestState"));
        //ServiceManager::Instance()->getService<StateMachine>().peekState()->onEnter();

		return true;
	}
	return false;
}

void BobberGame::start()
{
    Game::start();
}
