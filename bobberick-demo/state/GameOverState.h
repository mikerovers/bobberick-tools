#ifndef BOBBERICK_TOOLS_GAMEOVERSTATE_H
#define BOBBERICK_TOOLS_GAMEOVERSTATE_H
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"

class GameOverState : public GameState
{
public:
	void update() override;
	bool onEnter() override;
	bool onExit() override;
	bool shouldExit() override;
	void makeXPText() const;
	void makeHighscoreText() const;
	void makeGameOverText() const;
	void makeBackground() const;

	std::string getStateID() const override;
private:
	bool exitPressed = false;
	int highscorePos = 0;
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();

	void makeGui();
	void makeText() const;
};

#endif // BOBBERICK_TOOLS_GAMEOVERSTATE_H