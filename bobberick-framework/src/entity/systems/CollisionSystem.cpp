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
	if (colliderB.tag == "fire")
	{
		if (colliderA.entity->hasComponent<StatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<StatsComponent>();
			stats.getHit(500, false);
		}
		else if (colliderA.entity->hasComponent<PlayerStatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(500, false);
		}
	}

	if (colliderB.tag == "healthkit")
	{
		if (colliderA.entity->hasComponent<StatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<StatsComponent>();
			stats.healPercent(100);
		}
		else if (colliderA.entity->hasComponent<PlayerStatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(-100, true);
		}
	}

	if (colliderB.tag == "monster_projectile")
	{
		if (colliderA.entity->hasComponent<PlayerStatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<PlayerStatsComponent>();
			stats.getHit(50, true);
			colliderB.entity->destroy();
		}
	}

	if (colliderB.tag == "arrow")
	{
		if (colliderA.entity->hasComponent<StatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<StatsComponent>();
			stats.getHit(40, true);
			colliderB.entity->destroy();
		}
	}

	if (colliderB.tag == "bolt")
	{
		if (colliderA.entity->hasComponent<StatsComponent>())
		{
			auto& stats = colliderA.entity->getComponent<StatsComponent>();
			stats.getHit(80, true);
			colliderB.entity->destroy();
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
	auto collisionComponentEntities = entityManager.getAllEntitiesWithComponent<CollisionComponent>();

	for (auto& entity : collisionComponentEntities)
	{
		auto& colliderA = entity->getComponent<CollisionComponent>();


		for (auto& otherEntity : collisionComponentEntities)
		{
			auto& colliderB = otherEntity->getComponent<CollisionComponent>();
			if (colliderA.tag != colliderB.tag && helper.AABB(colliderA, colliderB))
			{
				handle_collision_aabb(colliderA, colliderB);
			}
		}
	}
}
