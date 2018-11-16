#ifndef BOBBERICK_TOOLS_COLLISIONSYSTEM_H
#define BOBBERICK_TOOLS_COLLISIONSYSTEM_H

#include "System.h"
#include "../components/CollisionComponent.h"

class CollisionSystem : public System
{
public:
    explicit CollisionSystem(EntityManager& entityManager);
	void handle_collision_aabb(CollisionComponent& colliderA, CollisionComponent& colliderB);
	void update() override;
};


#endif //BOBBERICK_TOOLS_COLLISIONSYSTEM_H
