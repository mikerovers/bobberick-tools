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
	bool readyForExit = false;
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	std::vector<Entity*> entities;

	void createAnimatedBackground();

	void makeStartGameButton() const;
	void makeOptionsButton() const;
	void makeAdvertisements() const;
	void makeLoadButton() const;
	void makeExitButton();
	void makeHelpButton() const;
};

#endif // BOBBERICK_TOOLS_MAINMENUSTATE_H