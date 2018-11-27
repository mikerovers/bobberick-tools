#ifndef BOBBERICK_TOOLS_LEVELSYSTEM_H
#define BOBBERICK_TOOLS_LEVELSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class LevelSystem : public System
{
public:
	explicit LevelSystem(EntityManager& entityManager);
	void update() override;
private:
	bool checkIfLevelFinished() const;
	void handleLevelFinished() const;
};


#endif //BOBBERICK_TOOLS_LEVELSYSTEM_H
