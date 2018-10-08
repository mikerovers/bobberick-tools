#include "CollisionSystem.h"
#include "../components/CollisionComponent.h"
#include "../Box2D/Box2D.h"

bool CollisionSystem::checkCollision(Entity entityA, Entity entityB)
{
	if (entityA.hasComponent<CollisionComponent>() && entityB.hasComponent<CollisionComponent>())
	{
		// if top of A < bottom of B --> no collision
		if ((entityA->y + entityA->h) <= entityB->y)
		{
			return false;
		}

		// if bottom of A > top of B --> no collision
		if (entityA->y >= entityB->y)
		{
			return false;
		}

		// if right of A < left of B --> no collision
		if ((entityA->x + entityA->w) <= entityB->x)
		{
			return false;
		}

		// if left of A > right of B --> no collision
		if (entityA->x >= entityB->x)
		{
			return false;
		}

		// collision occurred
		return true;
	}

	// given entities cannot collide
	return false;
}

