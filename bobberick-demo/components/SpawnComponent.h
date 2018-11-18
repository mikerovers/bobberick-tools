#ifndef BOBBERICK_TOOLS_SPAWNCOMPONENT_H
#define BOBBERICK_TOOLS_SPAWNCOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class SpawnComponent : public Component
{
public:
	explicit SpawnComponent(int id, std::string type, int countPer, int maxCount, int spawnTimer) : id(id), type(type), countPer(countPer), maxCount(maxCount), spawnTimer(spawnTimer) {};
	std::string type;
	int id;
	int countPer;
	int maxCount;
	int spawnTimer; // ms
};


#endif //BOBBERICK_TOOLS_SPAWNCOMPONENT_H
