#ifndef BOBBERICK_TOOLS_MAINMENUSTATE_H
#define BOBBERICK_TOOLS_MAINMENUSTATE_H
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"

class MainMenuState : public GameState
{
public:
	bool onEnter() override;
	bool onExit() override;
	void update() override;
	std::string getStateID() const override;
	bool shouldExit() override;

private:
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	bool _playGamePressed = false;
	std::vector<Entity*> entities;

	void createAnimatedBackground();

	void makeStartGameButton();
	void makeOptionsButton();
	void makeExitButton();

	void determineMovementDirection();
};

#endif // BOBBERICK_TOOLS_MAINMENUSTATE_H