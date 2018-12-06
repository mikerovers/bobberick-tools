#include "AISystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../services/PlayerStatsService.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/util/RandomGenerator.h"

#include "../../bobberick-demo/components/AIComponent.h"
#include "../../bobberick-demo/components/BulletMovementComponent.h"
#include "../../bobberick-demo/components/ShootComponent.h"
#include "../../bobberick-demo/components/PlayerComponent.h"
#include "../../bobberick-demo/components/StatsComponent.h"
#include "../../bobberick-demo/components/HealthBarComponent.h"
#include "../../bobberick-demo/components/EndBossComponent.h"
#include "../../bobberick-demo/components/SpawnComponent.h"
#include "../../bobberick-demo/components/SpawnedComponent.h"
#include "../../bobberick-demo/components/EnemyMovementComponent.h"
#include "../../bobberick-demo/components/SpawnMinionsSpellComponent.h"
#include "../../bobberick-demo/components/SprayComponent.h"
#include "../../bobberick-demo/factory/enemies/EnemyFactory.h"

#include <thread>
#include <chrono>

AISystem::AISystem(EntityManager& entityManager) : System(entityManager)
{
}

void AISystem::init()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AIComponent>())
	{
		initHealthBar(*entity);
		if (entity->hasComponent<CollisionComponent>())
		{
			auto& collisionComponent = entity->getComponent<CollisionComponent>();
			auto& transform = entity->getComponent<TransformComponent>();

			collisionComponent.collider.x = transform.position.x;
			collisionComponent.collider.y = transform.position.y;
			collisionComponent.collider.w = transform.width;
			collisionComponent.collider.h = transform.height;
		}
	}
}


void AISystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<SpawnComponent>())
	{
		executeSpawner(*entity);
	}

	for (auto& entity : entityManager.getAllEntitiesWithComponent<SprayComponent>())
	{
		executeSprayShoot(*entity);
	}

	int channelCounter = 2;
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AIComponent>())
	{
		auto& transform = entity->getComponent<TransformComponent>();

		// todo
		// check which directions are clear
		// adjust possible movements accordingly
		// delete properly
		// make shooting dependant on enemy type (cast/shoot/change of sprite)
		// make smoother

		executeShoot(*entity, channelCounter);
		executeSpell(*entity);
		applyHealthBar(*entity);
		applyMovement(*entity);

		//std::cout << transform.position.x << "\n";

		transform.update();
	}
}

void AISystem::executeSprayShoot(const Entity& entity)
{
	auto transformComponent = entity.getComponent<TransformComponent>();
	if (entity.hasComponent<TimerComponent>())
	{
		auto& timer = entity.getComponent<TimerComponent>();
		if (timer.isTimerFinished())
		{
			const auto numberOfBullets = 80;
			const auto angleStep = 360 / numberOfBullets;
			for (auto i = 0; i < numberOfBullets; ++i)
			{
				auto& projectile = ServiceManager::Instance()->getService<EntityManager>().addEntity();
				projectile.addComponent<BulletMovementComponent>();
				auto& projectileTransform = projectile.addComponent<TransformComponent>(
					transformComponent.position.x, transformComponent.position.y, 10, 10, 1);
				const int moveAngle = i * angleStep;
				const double xVel = 1 * cos(moveAngle);
				const double yVel = 1 * sin(moveAngle);
				projectileTransform.velocity.x = xVel;
				projectileTransform.velocity.y = yVel;
				ServiceManager::Instance()->getService<SoundManager>().playSound(100 + i, "bolt", 0);
				projectile.addComponent<SpriteComponent>("bolt");
				projectile.addComponent<CollisionComponent>("monster_projectile");
				for (const auto& group : entity.getGroups())
				{
					ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(projectile, group);
				}
				timer.setTimer(entity.getComponent<SprayComponent>().sprayTimer);
			}
		}
	}
}

void AISystem::executeSpell(Entity& entity)
{
	if (entity.hasComponent<TimerComponent>())
	{
		auto& timer = entity.getComponent<TimerComponent>();
		if (timer.isTimerFinished())
		{
			if (entity.hasComponent<SpawnMinionsSpellComponent>())
			{
				auto& spellComponent = entity.getComponent<SpawnMinionsSpellComponent>();
				if (spellComponent.phase > 2)
				{
					// return;
				}
				auto& transform = entity.getComponent<TransformComponent>();

				const double enemyX = transform.position.x;
				const double enemyY = transform.position.y;
				EnemyFactory enemyFactory = EnemyFactory{};

				std::string enemy_type;
				switch (spellComponent.phase)
				{
				case 0:
					{
						enemy_type = "zombie";
					}
					break;
				case 1:
					{
						enemy_type = "orc";
					}
					break;
				case 2:
				default:
					{
						enemy_type = "fireWizard";
					}
					break;
				}

				if (spellComponent.minionCount >= 8)
				{
					spellComponent.phase++;
					spellComponent.minionCount = 0;
					return;
				}

				const int randomXPosition = RandomGenerator{}.getRandomNumber(0, 4);

				for (auto i = 0; i < 4; i++)
				{
					auto& enemy = enemyFactory.getEnemy(1, enemy_type);
					auto& enemyTransform = enemy.getComponent<TransformComponent>();
					enemyTransform.position.x = enemyX - 50 * randomXPosition;
					enemyTransform.position.y = enemyY - 50 + i * 50;

					for (const auto& group : entity.getGroups())
					{
						ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(enemy, group);
					}

					initHealthBar(enemy);
					spellComponent.minionCount++;
				}

				timer.setTimer(5000);
			}
		}
	}
}

void AISystem::executeSpawner(Entity& entity)
{
	if (entity.hasComponent<TimerComponent>())
	{
		auto& timer = entity.getComponent<TimerComponent>();
		if (timer.isTimerFinished())
		{
			auto& spawnComponent = entity.getComponent<SpawnComponent>();
			auto& spawnerStats = entity.getComponent<StatsComponent>();

			bool isInRange = true;
			bool isAttacked = spawnerStats.getHP() < spawnerStats.getHPmax();
			for (auto& player : ServiceManager::Instance()
			                    ->getService<EntityManager>().getAllEntitiesWithComponent<PlayerComponent>())
			{
				if (!AISystem::isEntityInRange(entity, *player, 200))
				{
					isInRange = false;
				}
			}

			if (isInRange || isAttacked)
			{
			}
			else
			{
				return;
			}
			int spawnCounter = 0;

			for (auto& spawnedEnemy : ServiceManager::Instance()
			                          ->getService<EntityManager>().getAllEntitiesWithComponent<SpawnedComponent>())
			{
				auto& spawnedComponent = spawnedEnemy->getComponent<SpawnedComponent>();
				if (spawnedComponent.spawnerId == spawnComponent.id && spawnComponent.type == spawnedEnemy
				                                                                              ->getComponent<
					                                                                              CollisionComponent>().
				                                                                              tag)
				{
					spawnCounter++; // we found its spawn
				}
			}

			if (spawnCounter >= spawnComponent.maxCount)
			{
				return;
			}

			auto& statsComponent = entity.getComponent<StatsComponent>();
			auto& transformComponent = entity.getComponent<TransformComponent>();

			auto& enemy = EnemyFactory{}.spawnEnemy(1, spawnComponent.type, spawnComponent.id);
			for (const auto& group : entity.getGroups())
			{
				ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(enemy, group);
			}
			auto& enemyTransform = enemy.getComponent<TransformComponent>();
			enemyTransform.position.x = transformComponent.position.x + (transformComponent.width / 2);
			enemyTransform.position.y = transformComponent.position.y + transformComponent.height;
			initHealthBar(enemy);
			timer.setTimer(spawnComponent.spawnTimer);
		}
	}
}

void AISystem::executeShoot(Entity& entity, int& channelCounter)
{
	if (entity.hasComponent<ShootComponent>() && entity.hasComponent<TimerComponent>())
	{
		auto& timer = entity.getComponent<TimerComponent>();
		if (timer.isTimerFinished())
		{
			auto& transform = entity.getComponent<TransformComponent>();
			auto& sprite = entity.getComponent<SpriteComponent>();
			auto& collision = entity.getComponent<CollisionComponent>();

			auto& stats = entity.getComponent<StatsComponent>();
			auto& healthBar = entity.getComponent<HealthBarComponent>();

			double enemyX = transform.position.x;
			double enemyY = transform.position.y;

			for (auto& player : entityManager.getAllEntitiesWithComponent<PlayerComponent>())
			{
				channelCounter++;
				auto& playerTransform = player->getComponent<TransformComponent>();

				const double enemyXCenter = enemyX + transform.width / 2;
				const double enemyYCenter = enemyY + transform.height / 2;

				const auto angleX = playerTransform.position.x - enemyXCenter;
				const auto angleY = playerTransform.position.y - enemyYCenter;

				bool isInRange = AISystem::isEntityInRange(*player, entity, 300);

				if (isInRange)
				{
					if (angleX < 0)
					{
						sprite.flip = true;
					}
					else if (angleX > 0)
					{
						sprite.flip = false;
					}

					const float vectorLength = sqrt(angleX * angleX + angleY * angleY);
					const float dx = angleX / vectorLength;
					const float dy = angleY / vectorLength;

					auto& projectile = ServiceManager::Instance()->getService<EntityManager>().addEntity();
					projectile.addComponent<BulletMovementComponent>();
					auto& projectileTransform = projectile.addComponent<TransformComponent>(
						enemyXCenter + dx * 25, enemyYCenter + dy * 25, 10, 10, 1);
					projectileTransform.velocity.x = dx;
					projectileTransform.velocity.y = dy;

					sprite.setTexture("fireWizardCasting");
					// change to set entity to casting state (and change sprite accordingly)

					transform.velocity.x = 0;
					transform.velocity.y = 0;

					ServiceManager::Instance()->getService<SoundManager>().playSound(channelCounter, "bolt", 0);
					projectile.addComponent<SpriteComponent>("bolt");
					projectile.addComponent<CollisionComponent>("monster_projectile");
					for (const auto& group : entity.getGroups())
					{
						ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(projectile, group);
					}

					timer.setTimer(980);
				}
				else
				{
					sprite.setTexture("fireWizard");
				}
			}
		}
	}
}

void AISystem::initHealthBar(Entity& entity)
{
	auto& healthBar = entity.getComponent<HealthBarComponent>();
	auto& transform = entity.getComponent<TransformComponent>();
	if (entity.hasComponent<HealthBarComponent>())
	{
		int width = transform.width / 2;
		//int width = 50;
		healthBar.outerBox.addComponent<TransformComponent>(-1, -1, 12, width + 2, 1);
		healthBar.outerBox.addComponent<RectangleComponent>(0, 0, 0, false);

		healthBar.innerBox.addComponent<TransformComponent>(-1, -1, 10, width, 1);
		healthBar.innerBox.addComponent<RectangleComponent>(128, 128, 128, true);

		healthBar.healthBox.addComponent<TransformComponent>(-1, -1, 10, width, 1);
		healthBar.healthBox.addComponent<RectangleComponent>(255, 0, 0, true);
	}

	for (const auto& group : entity.getGroups())
	{
		auto& serviceManager = ServiceManager::Instance()->getService<EntityManager>();
		serviceManager.addEntityToGroup(healthBar.outerBox, group);
		serviceManager.addEntityToGroup(healthBar.innerBox, group);
		serviceManager.addEntityToGroup(healthBar.healthBox, group);
	}
}

void AISystem::kill(Entity& entity)
{
	if (entity.hasComponent<EndBossComponent>())
	{
		// win
	}
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	playerStats.xp += entity.getComponent<StatsComponent>().getHPmax();
	// animate destruction

	auto& healthBar = entity.getComponent<HealthBarComponent>();
	healthBar.healthBox.destroy();
	healthBar.outerBox.destroy();
	healthBar.innerBox.destroy();

	auto& entityTransform = entity.getComponent<TransformComponent>();

	auto& bloodPuddle = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	bloodPuddle.addComponent<TransformComponent>(entityTransform.position.x, entityTransform.position.y,
	                                             47, 47,
	                                             entityTransform.getScale() * 2);
	bloodPuddle.addComponent<SpriteComponent>("blood2");
	for (const auto& group : entity.getGroups())
	{
		ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(bloodPuddle, group);
	}
	entity.destroy();
}

bool AISystem::isEntityInRange(Entity& entity1, Entity& entity2, const int range)
{
	auto& entity1Transform = entity1.getComponent<TransformComponent>();
	auto& entity2Transform = entity2.getComponent<TransformComponent>();

	const double entity1XCenter = entity1Transform.position.x + entity1Transform.width / 2;
	const double entity1YCenter = entity1Transform.position.y + entity1Transform.height / 2;

	const double entity2XCenter = entity2Transform.position.x + entity2Transform.width / 2;
	const double entity2YCenter = entity2Transform.position.y + entity2Transform.height / 2;

	const double distance = sqrt(
		(entity1XCenter - entity2XCenter) * (entity1XCenter - entity2XCenter) + (entity1YCenter - entity2YCenter) * (
			entity1YCenter - entity2YCenter));

	return distance < range;
}

void AISystem::applyHealthBar(Entity& entity)
{
	auto& transform = entity.getComponent<TransformComponent>();
	auto& stats = entity.getComponent<StatsComponent>();
	auto& healthBar = entity.getComponent<HealthBarComponent>();

	double enemyX = transform.position.x;
	double enemyY = transform.position.y;

	if (entity.hasComponent<HealthBarComponent>())
	{
		int const hp = stats.getHP();
		if (hp < 1)
		{
			kill(entity);
		}

		auto& outBox = healthBar.outerBox.getComponent<TransformComponent>();
		auto& inBox = healthBar.innerBox.getComponent<TransformComponent>();
		auto& healBox = healthBar.healthBox.getComponent<TransformComponent>();

		if (stats.getHP() != stats.getHPmax())
		{
			outBox.visible = true;
			inBox.visible = true;
			healBox.visible = true;

			auto& x = healthBar.outerBox;
			outBox.position.y = enemyY - 10;
			outBox.position.x = enemyX + 15;

			inBox.position.y = enemyY - 9;
			inBox.position.x = enemyX + 16;

			healBox.position.y = enemyY - 9;
			healBox.position.x = enemyX + 16;

			const auto healthWidth = double(stats.getHP()) / double(stats.getHPmax()) * transform.width / 2;
			healthBar.healthBox.getComponent<TransformComponent>().width = healthWidth;
		}
		else
		{
			outBox.visible = false;
			inBox.visible = false;
			healBox.visible = false;
		}
	}
}

void AISystem::applyMovement(Entity& entity)
{
	if (!entity.hasComponent<EnemyMovementComponent>())
	{
		return;
	}
	auto& transform = entity.getComponent<TransformComponent>();
	auto& sprite = entity.getComponent<SpriteComponent>();
	auto& enemyMovement = entity.getComponent<EnemyMovementComponent>();
	const int gameWidth = ServiceManager::Instance()->getService<SettingsService>().gameWidth;
	const int gameHeight = ServiceManager::Instance()->getService<SettingsService>().gameHeight;

	const double speed = transform.speed / 10;

	const int moveChance = RandomGenerator{}.getRandomNumber(1, 100);
	const int moveAngle = RandomGenerator{}.getRandomNumber(0, 360);
	const double xVel = speed * cos(moveAngle);
	const double yVel = speed * sin(moveAngle);


	if (moveChance < 2 || enemyMovement.collided)
	{
		enemyMovement.collided = false;
		transform.velocity.x = xVel;
		transform.velocity.y = yVel;
		sprite.flip = xVel < 0;
	}
	else if (moveChance < 3)
	{
		enemyMovement.collided = false;
	}
	transform.update();

	double x = transform.position.x;
	double y = transform.position.y;
	if (x < 0)
	{
		transform.velocity.x = speed;
		sprite.flip = false;
	}
	if (x > gameWidth - 40)
	{
		transform.velocity.x = -speed;
		sprite.flip = true;
	}
	if (y < 0 + 50)
	{
		transform.velocity.y = speed;
	}
	if (y > gameHeight - 60)
	{
		transform.velocity.y = -speed;
	}

	sprite.moving = !(transform.velocity.x == 0 && transform.velocity.y == 0);

	if (entity.hasComponent<CollisionComponent>())
	{
		auto& collisionComponent = entity.getComponent<CollisionComponent>();
		collisionComponent.collider.x = transform.position.x;
		collisionComponent.collider.y = transform.position.y;
		collisionComponent.collider.w = transform.width;
		collisionComponent.collider.h = transform.height;
	}
}
