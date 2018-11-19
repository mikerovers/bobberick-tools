#ifndef BOBBERICK_TOOLS_SPAWNEDCOMPONENT_H
#define BOBBERICK_TOOLS_SPAWNEDCOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class SpawnedComponent : public Component
{
public:
	SpawnedComponent(int spawnerId) : spawnerId(spawnerId) {};
	int spawnerId;
};


#endif //BOBBERICK_TOOLS_SPAWNEDCOMPONENT_H
