#ifndef BOBBERICK_TOOLS_WORLDSERVICE_H
#define BOBBERICK_TOOLS_WORLDSERVICE_H

#include "Service.h"
#include "Dynamics/b2World.h"

class WorldService : public Service
{
public:
	WorldService();

	void init() override;
	b2World* getWorld();
	b2World* world;
};

#endif // BOBBERICK_TOOLS_WORLDSERVICE_H