#include "LevelSystem.h"
#include "../../bobberick-demo/components/AdvertisementComponent.h"
#include "../../bobberick-demo/components/ShootComponent.h"
#include "../../bobberick-demo/components/EndBossComponent.h"
#include "../../bobberick-demo/components/PlayerComponent.h"
#include "../../bobberick-demo/components/SpawnComponent.h"
#include "../../bobberick-demo/state/StateFactory.h"
#include "../../bobberick-demo/services/PlayerStatsService.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include <sstream>

LevelSystem::LevelSystem(EntityManager &entityManager) : System(entityManager), transition(entityManager.addEntity()), oldTransition(entityManager.addEntity())
{
	std::string const stateId = ServiceManager::Instance()->getService<StateMachine>().peekState().getStateID();

	// During construction, we're still in the old state, but this is the only oppurtunity to correctly place the rectangle before it gets drawn.
	// We have to list all possible states our level might have been pushed in from: loading from the main menu or starting from the skill screen.
	if (stateId != "mainmenu" && stateId != "skillscreen") {
		oldTransition.addComponent<TransformComponent>(0, 0, 704, 960, 1);
	}
	else {
		oldTransition.addComponent<TransformComponent>(-960, 0, 704, 960, 1);
	}

	oldTransition.addComponent<RectangleComponent>(255, 255, 255, true);
	oldTransition.getComponent<RectangleComponent>().overlay = true;

	transition.addComponent<TransformComponent>(970, 0, 704, 960, 1);
	transition.addComponent<RectangleComponent>(255, 255, 255, true);
	transition.getComponent<RectangleComponent>().overlay = true;
}

void LevelSystem::handleLevelFinished() const {
	StateFactory factory{};
	std::string const stateId = ServiceManager::Instance()->getService<StateMachine>().peekState().getStateID();
	std::string newStateId;
	if (stateId == "level_one") {
		newStateId = "Level2State";
	}
	else if (stateId == "level_two") {
		newStateId = "Level3State";
	}
	else if (stateId == "level_three") {
		newStateId = "Level4State";
	}
	else if (stateId == "level_four") {
		newStateId = "EndScreen";
	}
	if (!newStateId.empty()) {
		ServiceManager::Instance()->getService<StateMachine>().changeState(factory.createState(newStateId));
	}
}

bool LevelSystem::checkIfLevelFinished() const {
	auto endBossEntities = entityManager.getAllEntitiesWithComponent<EndBossComponent>();
	auto spawnEntities = entityManager.getAllEntitiesWithComponent<SpawnComponent>();
	endBossEntities.insert(std::end(endBossEntities), std::begin(spawnEntities),
		std::end(spawnEntities));
	return endBossEntities.empty();
}

void LevelSystem::update()
{
	std::string const stateId = ServiceManager::Instance()->getService<StateMachine>().peekState().getStateID();

	if (transition.getGroups().size() == 0) {
		entityManager.addEntityToGroup(transition, stateId);
		entityManager.addEntityToGroup(oldTransition, stateId);

		if (stateId != "level_one") {
			ServiceManager::Instance()->getService<PlayerStatsService>().invincible = true;
		}
	}

	auto& transitionPos = transition.getComponent<TransformComponent>();
	auto& oldTransitionPos = oldTransition.getComponent<TransformComponent>();

	if (oldTransitionPos.position.x > -960) {
		oldTransitionPos.position.x -= 10;
	} else {
		ServiceManager::Instance()->getService<PlayerStatsService>().invincible = false;
	}

	if (checkIfLevelFinished()) {
		ServiceManager::Instance()->getService<PlayerStatsService>().invincible = true;
		transitionPos.position.x -= 10;
		if (transitionPos.position.x < -10) {
			handleLevelFinished();
		}
	}
	else if (checkIfPlayerDied()) {
		handlePlayerDied();
	} else {
		transitionPos.position.x = 970;
	}
}

bool LevelSystem::checkIfPlayerDied() const {

	bool died = false;
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	if (playerStats.getHP() <= 0) {
		died = true;
	}
	return died;
}

void LevelSystem::handlePlayerDied() const {
	StateFactory factory{};
	ServiceManager::Instance()->getService<StateMachine>().changeState(factory.createState("GameOverState"));
}