#include "CollisionSystem.h"
#include "../CollisionHelper.h"
#include "../../../../bobberick-demo/components/HealthBarComponent.h"
#include "../../../../bobberick-demo/components/PlayerStatsComponent.h"

CollisionSystem::CollisionSystem(EntityManager& entityManager) : System(entityManager)
{
}

void CollisionSystem::handle_collision_aabb(CollisionComponent& colliderA, CollisionComponent& colliderB)
{
	std::cout << "Collision has happened! " << colliderA.tag << " : " << colliderB.tag << std::endl;


	if (colliderA.tag == "fire")
	{
		if (colliderB.entity->hasComponent<HealthBarComponent>())
		{
			std::cout << "Burning his buttocks: " << colliderB.tag << std::endl;
			auto playerStats = colliderB.entity->getComponent<PlayerStatsComponent>();
			playerStats.getHit(50000, false);
		}
		SDL_Delay(100000000000);
	}
}

void CollisionSystem::update()
{
	auto* helper = new CollisionHelper();

	for (auto& entity : entityManager.getAllEntitiesWithComponent<CollisionComponent>())
	{
		auto& colliderA = entity->getComponent<CollisionComponent>();

		for (auto& otherEntity : entityManager.getAllEntitiesWithComponent<CollisionComponent>())
		{
			auto& colliderB = otherEntity->getComponent<CollisionComponent>();
			if (colliderA.tag != colliderB.tag && helper->AABB(colliderA, colliderB))
			{
				handle_collision_aabb(colliderA, colliderB);
			}
		}
	}

	delete helper;
}
