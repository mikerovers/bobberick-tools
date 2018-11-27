#include "LevelSystem.h"
#include "../../bobberick-demo/components/AdvertisementComponent.h"
#include "../../bobberick-demo/components/ShootComponent.h"
#include "../../bobberick-demo/components/EndBossComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"
#include "../../bobberick-demo/components/SpawnComponent.h"
#include "../../bobberick-demo/state/StateFactory.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <sstream>

LevelSystem::LevelSystem(EntityManager &entityManager) : System(entityManager)
{

}

void LevelSystem::handleLevelFinished() const {
	StateFactory factory{};
	std::string const stateId = ServiceManager::Instance()->getService<StateMachine>().peekState()->getStateID();
	std::string newStateId = "";
	if (stateId == "level_one") {
		newStateId = "Level2State";
	}
	else if (stateId == "level_two") {
		newStateId = "Level3State";
	}
	else if (stateId == "level_three") {
		newStateId = "EndScreen";
	}
	if (newStateId != "") {
		ServiceManager::Instance()->getService<StateMachine>().changeState(factory.createState(newStateId));
	}
}

bool LevelSystem::checkIfLevelFinished() const {
	auto endBossEntities = entityManager.getAllEntitiesWithComponent<EndBossComponent>();
	auto spawnEntities = entityManager.getAllEntitiesWithComponent<SpawnComponent>();
	endBossEntities.insert(std::end(endBossEntities), std::begin(spawnEntities),
		std::end(spawnEntities));
	return endBossEntities.size() < 1;
}

void LevelSystem::update()
{
	if (checkIfLevelFinished()) {
		handleLevelFinished();
	}
	else if (checkIfPlayerDied()) {
		handlePlayerDied();
	}
}

bool LevelSystem::checkIfPlayerDied() const {

	bool died = false;
	for (auto& player : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>()) {
		auto& playerStats = player->getComponent<PlayerStatsComponent>();
		if (playerStats.getHP() <= 0) {
			died = true;
		}
	}
	return died;
}

void LevelSystem::handlePlayerDied() const {
	StateFactory factory{};
	ServiceManager::Instance()->getService<StateMachine>().changeState(factory.createState("MainMenuState"));
}