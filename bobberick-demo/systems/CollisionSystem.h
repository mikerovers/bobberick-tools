#ifndef BOBBERICK_TOOLS_COLLISIONSYSTEM_H
#define BOBBERICK_TOOLS_COLLISIONSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"

class CollisionSystem : public System
{
public:
    explicit CollisionSystem(EntityManager& entityManager);

	virtual void handle_collision_aabb(CollisionComponent& colliderA, CollisionComponent& colliderB);

	virtual void handle_collision_aabb_direction(CollisionComponent& colliderA, CollisionComponent& colliderB, int const direction);
	void update() override;
};


#endif //BOBBERICK_TOOLS_COLLISIONSYSTEM_H
