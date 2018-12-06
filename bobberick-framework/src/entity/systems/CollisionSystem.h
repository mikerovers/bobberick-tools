#ifndef BOBBERICK_TOOLS_COLLISIONSYSTEM_H
#define BOBBERICK_TOOLS_COLLISIONSYSTEM_H

#include "System.h"
#include "../components/CollisionComponent.h"

class CollisionSystem : public System
{
public:
    explicit CollisionSystem(EntityManager& entityManager);
	void handle_collision_aabb(CollisionComponent& colliderA, CollisionComponent& colliderB);
	void handle_collision_aabb_direction(CollisionComponent& colliderA, CollisionComponent& colliderB, int direction);
	void update() override;
};


#endif //BOBBERICK_TOOLS_COLLISIONSYSTEM_H
