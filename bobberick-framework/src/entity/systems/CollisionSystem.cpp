#include "CollisionSystem.h"
#include "../CollisionHelper.h"
#include "../../../../bobberick-demo/components/HealthBarComponent.h"
#include "../../../../bobberick-demo/components/PlayerStatsComponent.h"

CollisionSystem::CollisionSystem(EntityManager& entityManager) : System(entityManager)
{
}

void CollisionSystem::handle_collision_aabb(CollisionComponent& colliderA, CollisionComponent& colliderB)
{
	if (colliderA.tag == "fire")
	{
		if (colliderB.entity->hasComponent<StatsComponent>())
		{
			std::cout << "Burning his buttocks: " << colliderB.tag << std::endl;
			auto stats = colliderB.entity->getComponent<StatsComponent>();
			stats.getHit(500, false);
		}
		else if (colliderB.entity->hasComponent<PlayerStatsComponent>())
		{
			std::cout << "Burning his buttocks: " << colliderB.tag << std::endl;
			auto stats = colliderB.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(500, false);
		}
	}

	if (colliderA.tag == "healthkit")
	{
		if (colliderB.entity->hasComponent<StatsComponent>())
		{
			std::cout << "Healing: " << colliderB.tag << std::endl;
			auto stats = colliderB.entity->getComponent<StatsComponent>();
			stats.healPercent(100);
		}
		else if (colliderB.entity->hasComponent<PlayerStatsComponent>())
		{
			std::cout << "Healing: " << colliderB.tag << std::endl;
			auto stats = colliderB.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(-100, true);
		}
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
