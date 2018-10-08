#ifndef BOBBERICK_TOOLS_COLLISIONMANAGER_H
#define BOBBERICK_TOOLS_COLLISIONMANAGER_H

#include "System.h"

class CollisionSystem : public System
{
public:
	bool checkCollision(Entity entityA, Entity entityB);
};

#endif //BOBBERICK_TOOLS_COLLISIONMANAGER_H