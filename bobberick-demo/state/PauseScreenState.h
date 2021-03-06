#ifndef BOBBERICK_TOOLS_PAUSESCREENTATE_H
#define BOBBERICK_TOOLS_PAUSESCREENTATE_H
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"

class PauseScreenState : public GameState
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
	
	void createPauseText() const;
	void createResumeButton() const;
	void createHelpButton() const;
	void makeOptionsButton() const;
	void createSaveButton() const;
	void createExitButton();
	void createBackground() const;
};

#endif //BOBBERICK_TOOLS_PAUSESCREENTATE_H