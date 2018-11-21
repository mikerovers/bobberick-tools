#include "CollisionSystem.h"
#include "../CollisionHelper.h"
#include "../../../../bobberick-demo/components/HealthBarComponent.h"
#include "../../../../bobberick-demo/components/PlayerStatsComponent.h"
#include "../../../../bobberick-demo/components/BulletMovementComponent.h"
#include "../../../../bobberick-demo/components/EnemyMovementComponent.h"
#include "../../../../bobberick-demo/components/PlayerMovementComponent.h"

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

	if (colliderB.tag == "water")
	{
	}

	if (colliderB.tag == "aabb_rectangle")
	{
		if (colliderA.entity->hasComponent<TransformComponent>())
		{
			auto& transform = colliderA.entity->getComponent<TransformComponent>();


			//transform.velocity * -1;


			//transform.velocity.x = -transform.velocity.x;
			//transform.velocity.y = -transform.velocity.y;
			//transform.position.x += transform.velocity.x * 50;
			//transform.position.y += transform.velocity.y * 50;

			if (colliderA.tag == "player")
			{
				//auto& playerMovement = colliderA.entity->getComponent <PlayerMovementComponent> ();
				//playerMovement.collided = true;
				//transform.position.x += -transform.velocity.x * 5;
				//transform.position.y += -transform.velocity.y * 5;
			}
			else {
				auto& enemyMovement = colliderA.entity->getComponent<EnemyMovementComponent>();
				enemyMovement.collided = true;
				transform.position.x += -transform.velocity.x * 5;
				transform.position.y += -transform.velocity.y * 5;
			}
			transform.velocity.zero();
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

		cC.collider.x = tC.position.x;
		cC.collider.y = tC.position.y;
		cC.collider.w = tC.width;
		cC.collider.h = tC.height;
	}

	const auto removeNonPlayersAndMonsters = [](Entity* entity) -> bool
	{
		return true;
		return !entity->hasComponent<PlayerStatsComponent>() || !entity->hasComponent<StatsComponent>();
	};

	auto collisionComponentEntities = entityManager.getAllEntitiesWithComponent<CollisionComponent>();
	auto playerAndMonsterEntities = entityManager.getAllEntitiesWithComponent<StatsComponent>();
	auto playerEntities = entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>();
	playerAndMonsterEntities.insert(std::end(playerAndMonsterEntities), std::begin(playerEntities), std::end(playerEntities));

	for (auto& entity : playerAndMonsterEntities)
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
