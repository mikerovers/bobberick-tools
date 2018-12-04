#include "CollisionSystem.h"
#include "../CollisionHelper.h"
#include "../../../../bobberick-demo/services/PlayerStatsService.h"
#include "../../services/ServiceManager.h"
#include "../../../../bobberick-demo/components/HealthBarComponent.h"
#include "../../../../bobberick-demo/components/StatsComponent.h"
#include "../../../../bobberick-demo/components/PlayerComponent.h"
#include "../../../../bobberick-demo/components/BulletMovementComponent.h"
#include "../../../../bobberick-demo/components/EnemyMovementComponent.h"
#include "../../../../bobberick-demo/components/PlayerMovementComponent.h"
#include "../../../../bobberick-demo/components/PickUpComponent.h"
#include "../../../../bobberick-demo/components/InventoryComponent.h"
#include "../../../../bobberick-demo/components/InventorySlotComponent.h"

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
			stats.getHit(10, false);
		}
		else if (colliderA.entity->hasComponent<PlayerComponent>())
		{
			auto& stats = ServiceManager::Instance()->getService<PlayerStatsService>();
			stats.getHit(10, false);
		}
	}

	if (colliderB.entity->hasComponent<PickUpComponent>())
	{
		if (colliderA.entity->hasComponent<PlayerComponent>())
		{
			auto const serviceManager = ServiceManager::Instance();
			if (colliderB.tag == "healthkit")
			{
				serviceManager->getService<PlayerStatsService>().heal(20);;
				colliderB.entity->setActive(false);
				for (const auto& group : colliderB.entity->getGroups())
				{
					colliderB.entity->removeGroup(group);
					colliderB.entity->destroy();
				}
			}
			else if (colliderB.tag == "weapon")
			{
				std::vector<Entity*> iEntities = ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<InventorySlotComponent>();
				for (Entity* iEntity : iEntities)
				{
					if (iEntity->getComponent<InventorySlotComponent>().textureID == "null")
					{
						iEntity->getComponent<InventorySlotComponent>().textureID = colliderB.entity->getComponent<WeaponComponent>().textureID;
						iEntity->addComponent<SpriteComponent>(iEntity->getComponent<InventorySlotComponent>().textureID.c_str(), true);
						break;
					}
				}

				colliderA.entity->getComponent<InventoryComponent>().pickUp(colliderB.entity->getComponent<WeaponComponent>());
				for (const auto& group : colliderB.entity->getGroups())
				{
					colliderB.entity->removeGroup(group);
					colliderB.entity->destroy();
				}
			}
		}
	}
	// if (colliderB.tag == "healthkit")
	// {
	// 	if (colliderA.entity->hasComponent<StatsComponent>())
	// 	{
	// 		auto& stats = colliderA.entity->getComponent<StatsComponent>();
	// 		stats.healPercent(100);
	// 	}
	// 	else if (colliderA.entity->hasComponent<PlayerComponent>())
	// 	{
	// 		auto& stats = ServiceManager::Instance()->getService<PlayerStatsService>();
	// 		stats.heal(5);
	// 	}
	// }

	if (colliderB.tag == "monster_projectile")
	{
		if (colliderA.entity->hasComponent<PlayerComponent>())
		{
			auto& stats = ServiceManager::Instance()->getService<PlayerStatsService>();
			stats.getHit(5, true);
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
			else
			{
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

	auto collisionComponentEntities = entityManager.getAllEntitiesWithComponent<CollisionComponent>();
	auto playerAndMonsterEntities = entityManager.getAllEntitiesWithComponent<StatsComponent>();
	auto playerEntities = entityManager.getAllEntitiesWithComponent<PlayerComponent>();
	playerAndMonsterEntities.insert(std::end(playerAndMonsterEntities), std::begin(playerEntities),
	                                std::end(playerEntities));

	auto nonMonsterProjectileComponentEntities = entityManager.getAllEntitiesWithComponent<CollisionComponent>();
	nonMonsterProjectileComponentEntities.erase(
		std::remove_if(nonMonsterProjectileComponentEntities.begin(), nonMonsterProjectileComponentEntities.end(),
			[](Entity* entity)
	{
		auto tag = entity->getComponent<CollisionComponent>().tag;
		return tag == "monster_projectile" || tag == "chicken" || tag == "zombie" || tag == "orc" || tag == "fireWizard" || tag == "manufacturer";

	}), nonMonsterProjectileComponentEntities.end()
		);

	for (auto& entity : playerAndMonsterEntities)
	{
		auto& colliderA = entity->getComponent<CollisionComponent>();
		if (colliderA.tag != "player")
		{
			for (auto& otherEntity : nonMonsterProjectileComponentEntities)
			{
				auto& colliderB = otherEntity->getComponent<CollisionComponent>();

				if (colliderA.tag != colliderB.tag && helper.AABB(colliderA, colliderB))
				{
					handle_collision_aabb(colliderA, colliderB);
				}
			}
		}
		else
		{
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
}
