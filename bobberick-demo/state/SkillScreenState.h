#ifndef BOBBERICK_TOOLS_SKILLSCREENSTATE_H
#define BOBBERICK_TOOLS_SKILLSCREENSTATE_H
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/util/TextFormatter.h"
#include "../../bobberick-framework/src/entity/Entity.h"
#include "../services/PlayerStatsService.h"

class SkillScreenState : public GameState
{
public:
	SkillScreenState() : xpText(entityManager.addEntity()),
		xpImage(entityManager.addEntity()),
		hpCost(entityManager.addEntity()), 
		hpLevel(entityManager.addEntity()), 
		hpValue(entityManager.addEntity()), 
		hpNext(entityManager.addEntity()),
		atCost(entityManager.addEntity()),
		atLevel(entityManager.addEntity()),
		atValue(entityManager.addEntity()),
		atNext(entityManager.addEntity()), 
		shdTimeCost(entityManager.addEntity()),
		shdTimeLevel(entityManager.addEntity()),
		shdTimeValue(entityManager.addEntity()),
		shdTimeNext(entityManager.addEntity()), 
		shdRecovCost(entityManager.addEntity()),
		shdRecovLevel(entityManager.addEntity()),
		shdRecovValue(entityManager.addEntity()),
		shdRecovNext(entityManager.addEntity()) 
	{
		entityManager.addEntityToGroup(xpImage, getStateID());
		entityManager.addEntityToGroup(xpText, getStateID());
		entityManager.addEntityToGroup(hpCost, getStateID());
		entityManager.addEntityToGroup(hpLevel, getStateID());
		entityManager.addEntityToGroup(hpValue, getStateID());
		entityManager.addEntityToGroup(hpNext, getStateID());
		entityManager.addEntityToGroup(atCost, getStateID());
		entityManager.addEntityToGroup(atLevel, getStateID());
		entityManager.addEntityToGroup(atValue, getStateID());
		entityManager.addEntityToGroup(atNext, getStateID());
		entityManager.addEntityToGroup(shdTimeCost, getStateID());
		entityManager.addEntityToGroup(shdTimeLevel, getStateID());
		entityManager.addEntityToGroup(shdTimeValue, getStateID());
		entityManager.addEntityToGroup(shdTimeNext, getStateID());
		entityManager.addEntityToGroup(shdRecovCost, getStateID());
		entityManager.addEntityToGroup(shdRecovLevel, getStateID());
		entityManager.addEntityToGroup(shdRecovValue, getStateID());
		entityManager.addEntityToGroup(shdRecovNext, getStateID());
	}

	bool onEnter() override;
	bool onExit() override;
	void update() override;
	std::string getStateID() const override;
	bool shouldExit() override;

private:
	bool readyForExit = false;
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();

	void makeStartGameButton() const;
	void makeHpButton();
	void makeAtButton();
	void makeShdTimeButton();
	void makeShdRecovButton();
	void makeExitButton();
	void makeBackground() const;

	void makeHpText() const;
	void makeAtText() const;
	void makeShdTimeText() const;
	void makeShdRecovText() const;

	void updateHpText(PlayerStatsService& playerStats);
	void updateAtText(PlayerStatsService& playerStats);
	void updateShdTimeText(PlayerStatsService& playerStats);
	void updateShdRecovText(PlayerStatsService& playerStats);

	TextFormatter textFormatter = TextFormatter();

	Entity& xpImage;
	Entity& xpText;

	Entity& hpCost;
	Entity& hpLevel;
	Entity& hpValue;
	Entity& hpNext;

	Entity& atCost;
	Entity& atLevel;
	Entity& atValue;
	Entity& atNext;

	Entity& shdTimeCost;
	Entity& shdTimeLevel;
	Entity& shdTimeValue;
	Entity& shdTimeNext;

	Entity& shdRecovCost;
	Entity& shdRecovLevel;
	Entity& shdRecovValue;
	Entity& shdRecovNext;

};

#endif // BOBBERICK_TOOLS_SKILLSCREENSTATE_H