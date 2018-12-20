#ifndef BOBBERICK_TOOLS_LEVELSYSTEM_H
#define BOBBERICK_TOOLS_LEVELSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../../bobberick-framework/src/entity/Entity.h"

class LevelSystem : public System
{
public:
	explicit LevelSystem(EntityManager& entityManager);
	void update() override;
private:
	bool checkIfLevelFinished() const;
	void handleLevelFinished() const;

	bool checkIfPlayerDied() const;
	void handlePlayerDied() const;

	Entity& transition;
	Entity& oldTransition;
};


#endif //BOBBERICK_TOOLS_LEVELSYSTEM_H
