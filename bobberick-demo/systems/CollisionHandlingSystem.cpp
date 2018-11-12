#include "CollisionHandlingSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-demo/components/BulletComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"
#include "../../bobberick-demo/components/AIComponent.h"
CollisionHandlingSystem::CollisionHandlingSystem(EntityManager &entityManager) : System(entityManager)
{

}

void CollisionHandlingSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<CollisionComponent>()) {
		if (entity->hasComponent<PlayerStatsComponent>()) {
			handlePlayerCollision(entity);
		}
		else if (entity->hasComponent<AIComponent>()) {
			handleAICollision(entity);
		}
	}
}

void CollisionHandlingSystem::handlePlayerCollision(std::shared_ptr<Entity> entity)
{
	auto& collision = entity->getComponent<CollisionComponent>();
	if (collision.collidingWith.size() > 0) {
		for (auto& otherEntity : collision.collidingWith) {
			if (otherEntity->getComponent<CollisionComponent>().tag == "enemyBullet") { // getting hit
				auto& playerStats = entity->getComponent<PlayerStatsComponent>();
				playerStats.stats->getHit(otherEntity->getComponent<BulletComponent>().damage, 0);
				otherEntity->destroy();
				//remove bullet
				// do damage
			}
		}

	}
}

void CollisionHandlingSystem::handleAICollision(std::shared_ptr<Entity> entity)
{
	auto& collision = entity->getComponent<CollisionComponent>();
	if (collision.collidingWith.size() > 0) {
		for (auto& otherEntity : collision.collidingWith) {
			if (otherEntity->getComponent<CollisionComponent>().tag == "playerBullet") { // getting hit
				auto& stats = entity->getComponent<StatsComponent>();
				stats.getHit(otherEntity->getComponent<BulletComponent>().damage, 0);
				otherEntity->destroy();
				//remove bullet
				// do damage
			}
		}

	}
}