#ifndef BOBBERICK_TOOLS_SPAWNMINIONSSPELLCOMPONENT_H
#define BOBBERICK_TOOLS_SPAWNMINIONSSPELLCOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class SpawnMinionsSpellComponent : public Component
{
public:
	int phase = 0;
	int minionCount = 0;
};


#endif //BOBBERICK_TOOLS_SPAWNMINIONSSPELLCOMPONENT_H
