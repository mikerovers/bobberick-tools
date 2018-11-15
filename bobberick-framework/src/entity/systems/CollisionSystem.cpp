#include "CollisionSystem.h"
#include "../CollisionHelper.h"
#include "../../../../bobberick-demo/components/HealthBarComponent.h"
#include "../../../../bobberick-demo/components/PlayerStatsComponent.h"
#include "../../../../bobberick-demo/components/BulletMovementComponent.h"

CollisionSystem::CollisionSystem(EntityManager& entityManager) : System(entityManager)
{
}

void CollisionSystem::handle_collision_aabb(CollisionComponent& colliderA, CollisionComponent& colliderB)
{
	if (colliderA.tag == "fire")
	{
		if (colliderB.entity->hasComponent<StatsComponent>())
		{
			auto& stats = colliderB.entity->getComponent<StatsComponent>();
			stats.getHit(500, false);
		}
		else if (colliderB.entity->hasComponent<PlayerStatsComponent>())
		{
			auto& stats = colliderB.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(500, false);
		}
	}

	if (colliderA.tag == "healthkit")
	{
		if (colliderB.entity->hasComponent<StatsComponent>())
		{
			auto& stats = colliderB.entity->getComponent<StatsComponent>();
			stats.healPercent(100);
		}
		else if (colliderB.entity->hasComponent<PlayerStatsComponent>())
		{
			auto& stats = colliderB.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(-100, true);
		}
	}

	if (colliderA.tag == "monster_projectile")
	{
		if (colliderB.entity->hasComponent<PlayerStatsComponent>())
		{
			auto& stats = colliderB.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(50, true);
			colliderA.entity->destroy();
		}
	}

	if (colliderA.tag == "arrow")
	{
		if (colliderB.entity->hasComponent<StatsComponent>())
		{
			std::cout << "Is shot: " << colliderB.tag << std::endl;
			auto& stats = colliderB.entity->getComponent<StatsComponent>();
			stats.getHit(40, true);
			colliderA.entity->destroy();
		}
	}

	if (colliderA.tag == "bolt")
	{
		if (colliderB.entity->hasComponent<StatsComponent>())
		{
			std::cout << "Is shot: " << colliderB.tag << std::endl;
			auto& stats = colliderB.entity->getComponent<StatsComponent>();
			stats.getHit(80, true);
			colliderA.entity->destroy();
		}
	}
}

void CollisionSystem::update()
{
	CollisionHelper helper;

	for (auto& entity : entityManager.getAllEntitiesWithComponent<BulletMovementComponent>())
	{
		auto& tC = entity->getComponent<TransformComponent>();
		auto& cC = entity->getComponent<CollisionComponent>();

		cC.collider.x = tC.position.getX();
		cC.collider.y = tC.position.getY();
		cC.collider.w = tC.width;
		cC.collider.h = tC.height;
	}

	for (auto& entity : entityManager.getAllEntitiesWithComponent<CollisionComponent>())
	{
		auto& colliderA = entity->getComponent<CollisionComponent>();

		for (auto& otherEntity : entityManager.getAllEntitiesWithComponent<CollisionComponent>())
		{
			auto& colliderB = otherEntity->getComponent<CollisionComponent>();
			if (colliderA.tag != colliderB.tag && helper.AABB(colliderA, colliderB))
			{
				handle_collision_aabb(colliderA, colliderB);
			}
		}
	}
}
