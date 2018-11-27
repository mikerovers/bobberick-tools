#ifndef BOBBERICK_TOOLS_SKILLSCREENSTATE_H
#define BOBBERICK_TOOLS_SKILLSCREENSTATE_H
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../components/SkillsComponent.h"

class SkillScreenState : public GameState
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
	SkillsComponent skills;

	void makeStartGameButton();
	void makeHpButton();
	void makeAtButton();
	void makeDfButton();
	void makeShdTimeButton();
	void makeShdRecovButton();
	void makeExitButton();
};

#endif // BOBBERICK_TOOLS_SKILLSCREENSTATE_H