#ifndef BOBBERICK_TOOLS_COLLISIONCOMPONENT_H
#define BOBBERICK_TOOLS_COLLISIONCOMPONENT_H

#include "../Component.h"
#include "../Entity.h"

class CollisionComponent : public Component
{
private:
	Entity otherEntity;
};

#endif // BOBBERICK_TOOLS_COLLISIONCOMPONENT_H