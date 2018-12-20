#include "AISystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../services/PlayerStatsService.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-framework/src/entity/components/ParticleSystemComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/util/RandomGenerator.h"

#include "../../bobberick-demo/components/AIComponent.h"
#include "../../bobberick-demo/components/BulletMovementComponent.h"
#include "../../bobberick-demo/components/ShootComponent.h"
#include "../../bobberick-demo/components/PlayerComponent.h"
#include "../../bobberick-demo/components/DamageComponent.h"
#include "../../bobberick-demo/components/StatsComponent.h"
#include "../../bobberick-demo/components/LimitedTimeComponent.h"
#include "../../bobberick-demo/components/PickUpComponent.h"
#include "../../bobberick-demo/components/HealthBarComponent.h"
#include "../../bobberick-demo/components/ChaseComponent.h"
#include "../../bobberick-demo/components/EndBossComponent.h"
#include "../../bobberick-demo/components/SpawnComponent.h"
#include "../../bobberick-demo/components/SpawnedComponent.h"
#include "../../bobberick-demo/components/EnemyMovementComponent.h"
#include "../../bobberick-demo/components/SpawnMinionsSpellComponent.h"
#include "../../bobberick-demo/components/SprayComponent.h"
#include "../../bobberick-demo/factory/enemies/EnemyFactory.h"
#include "../../bobberick-demo/factory/WeaponFactory.h"

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
	for (auto& entity : entityManager.getAllEntitiesWithComponent<LimitedTimeComponent>())
	{
		executeLimitedTime(*entity);
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

		executeChase(*entity);
		executeShoot(*entity, channelCounter);
		executeSpell(*entity);
		applyHealthBar(*entity);
		applyMovement(*entity);

		transform.update();
		if (entity->hasComponent<CollisionComponent>())
		{
			auto& collisionComponent = entity->getComponent<CollisionComponent>();
			collisionComponent.collider.x = transform.position.x;
			collisionComponent.collider.y = transform.position.y;
			collisionComponent.collider.w = transform.width;
			collisionComponent.collider.h = transform.height;
		}
	}
}

void AISystem::executeLimitedTime(Entity& entity)
{
	auto transformComponent = entity.getComponent<TransformComponent>();
	if (entity.hasComponent<TimerComponent>() && entity.hasComponent<LimitedTimeComponent>())
	{
		auto& timer = entity.getComponent<TimerComponent>();
		if (timer.isTimerFinished())
		{
			entity.destroy();
		}
	}
}

void AISystem::executeChase(Entity& entity)
{
	auto transformComponent = entity.getComponent<TransformComponent>();
	if (entity.hasComponent<TimerComponent>() && entity.hasComponent<ChaseComponent>())
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

			for (auto& player : ServiceManager::Instance()
			                    ->getService<EntityManager>().getAllEntitiesWithComponent<PlayerComponent>())
			{
				auto& playerTransform = player->getComponent<TransformComponent>();
				RandomGenerator random = RandomGenerator{};
				bool isInCloseRange = AISystem::isEntityInRange(entity, *player, 200);
				bool isInFarRange = AISystem::isEntityInRange(entity, *player, 350);
				int rangeModifier = isInCloseRange ? 50 : isInFarRange ? 250 : 400;
				//	int rangeModifier = !isInFarRange ? !isInCloseRange ? 350 : 250 : 50;

				int deviationX = random.getRandomNumber(0, 1 * rangeModifier);
				int deviationY = random.getRandomNumber(0, 1 * rangeModifier);

				const double enemyXCenter = enemyX + transform.width / 2;
				const double enemyYCenter = enemyY + transform.height / 2;

				const auto angleX = playerTransform.position.x - enemyXCenter + deviationX;
				const auto angleY = playerTransform.position.y - enemyYCenter + deviationY;

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

				transform.velocity.x = dx * transform.speed / 3;
				transform.velocity.y = dy * transform.speed / 3;
				sprite.moving = true;
			}
			timer.setTimer(100);
		}
	}
}

void AISystem::executeSprayShoot(const Entity& entity)
{
	auto transformComponent = entity.getComponent<TransformComponent>();
	if (entity.hasComponent<TimerComponent>() && entity.hasComponent<StatsComponent>())
	{
		auto& timer = entity.getComponent<TimerComponent>();
		auto& stats = entity.getComponent<StatsComponent>();
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
				projectile.addComponent<SpriteComponent>("bolt", 4);
				projectile.addComponent<CollisionComponent>("monster_projectile");
				projectile.addComponent<DamageComponent>(stats.attack());
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
				if (spellComponent.max <= spellComponent.current)
				{
					return;
				}
				if (spellComponent.phase > 2)
				{
					// return;
				}
				auto& transform = entity.getComponent<TransformComponent>();

				const double enemyX = transform.position.x;
				const double enemyY = transform.position.y;

				const double enemyXCenter = enemyX + transform.width / 2;
				const double enemyYCenter = enemyY + transform.height / 2;

				const int enemyLevel = entity.getComponent<StatsComponent>().getLevel();
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

				auto& spawnCircle = ServiceManager::Instance()->getService<EntityManager>().addEntity();
				spawnCircle.addComponent<TransformComponent>(enemyX, enemyY, 128, 128, 1);
				auto& spawnCircleSpriteComponent = spawnCircle.addComponent<SpriteComponent
				>("spawnCircle", 4, 4, 6, 10);
				spawnCircleSpriteComponent.moving = true;
				auto& spawnCircleTimer = spawnCircle.addComponent<TimerComponent>();
				spawnCircleTimer.setTimer(1000);
				spawnCircle.addComponent<LimitedTimeComponent>();
				spawnCircle.addComponent<EnemyMovementComponent>();

				for (const auto& group : entity.getGroups())
				{
					ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(spawnCircle, group);
				}


				const int randomXPosition = RandomGenerator{}.getRandomNumber(0, 4);
				const int randomBool = RandomGenerator{}.getRandomNumber(0, 1);

				for (auto i = 0; i < 4; i++)
				{
					if (enemyLevel > 3)
					{
						if (i == 3)
						{
							enemy_type = "bird";
						}
					}

					auto& enemy = enemyFactory.getEnemy(entity.getComponent<StatsComponent>().getLevel(), enemy_type);
					auto& enemyTransform = enemy.getComponent<TransformComponent>();
					enemyTransform.position.x = (randomBool ? 25 : -25) + enemyXCenter;
					enemyTransform.position.y = (randomBool ? -25 : 25) + enemyYCenter;

					for (const auto& group : entity.getGroups())
					{
						ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(enemy, group);
					}

					initHealthBar(enemy);
					spellComponent.minionCount++;
				}


				spellComponent.current++;

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
		if (timer.isTimerFinished() && entity.hasComponent<SpawnComponent>())
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

			auto& enemy = EnemyFactory{}.spawnEnemy(statsComponent.getLevel() - 1, statsComponent.getLevel() + 2,
			                                        spawnComponent.type, spawnComponent.id);
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

				bool isInRange = AISystem::isEntityInRange(*player, entity, (240 + (stats.getLevel() * 40)));

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

					stats.getLevel() < 6
						? sprite.setTexture("fireWizardCasting")
						: stats.getLevel() < 9
						? sprite.setTexture("iceWizardCasting")
						: sprite.setTexture("metalWizardCasting");
					// change to set entity to casting state (and change sprite accordingly)

					transform.velocity.x = 0;
					transform.velocity.y = 0;

					ServiceManager::Instance()->getService<SoundManager>().playSound(channelCounter, "bolt", 0);
					projectile.addComponent<SpriteComponent>("bolt", 4);
					projectile.addComponent<CollisionComponent>("monster_projectile");
					projectile.addComponent<DamageComponent>(stats.attack());
					for (const auto& group : entity.getGroups())
					{
						ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(projectile, group);
					}

					timer.setTimer(980);
				}
				else
				{
					stats.getLevel() < 6
						? sprite.setTexture("fireWizard")
						: stats.getLevel() < 9
						? sprite.setTexture("iceWizard")
						: sprite.setTexture("metalWizard");
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
	int spawnChance = 0;
	auto& killedTransform = entity.getComponent<TransformComponent>();
	if (entity.hasComponent<SpawnComponent>())
	{
		EnemyFactory enemyFactory = EnemyFactory{};
		auto& enemy = enemyFactory.getBoss(entity.getComponent<StatsComponent>().getLevel());
		auto& enemyTransform = enemy.getComponent<TransformComponent>();
		enemyTransform.position.x = killedTransform.position.x;
		enemyTransform.position.y = killedTransform.position.y + 50;
		for (const auto& group : entity.getGroups())
		{
			ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(enemy, group);
		}
		initHealthBar(enemy);
		auto endBossEntities = ServiceManager::Instance()
		                       ->getService<EntityManager>().getAllEntitiesWithComponent<EndBossComponent>();
		if (endBossEntities.size() <= 1)
		{
			ServiceManager::Instance()->getService<SoundManager>().playMusic("boss", -1);
		}
	}
	else if (entity.hasComponent<EndBossComponent>())
	{
		const auto state = ServiceManager::Instance()->getService<StateMachine>().peekState().getStateID();

		spawnChance = state != "level_four" ? 100 : 0;
		auto endBossEntities = ServiceManager::Instance()
		                       ->getService<EntityManager>().getAllEntitiesWithComponent<EndBossComponent>();
		auto& particleSystem = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(
			particleSystem,
			ServiceManager::Instance()
			->getService<StateMachine>().peekState().getStateID());
		particleSystem.addComponent<TransformComponent>(
			entity.getComponent<TransformComponent>().position.x,
			entity.getComponent<TransformComponent>().position.y,
			32, 32, 1);
		particleSystem.addComponent<ParticleSystemComponent>("blood1", 40, 200, 5000);
		particleSystem.getComponent<ParticleSystemComponent>().addTexture("blood2");
		particleSystem.getComponent<ParticleSystemComponent>().addTexture("blood3");
		particleSystem.getComponent<ParticleSystemComponent>().addTexture("blood4");
		particleSystem.getComponent<ParticleSystemComponent>().addTexture("blood5");
		if (endBossEntities.size() < 2)
		{

			if (state == "level_one")
			{
				ServiceManager::Instance()->getService<SoundManager>().playMusic("level1", -1);
			}
			else if (state == "level_two")
			{
				ServiceManager::Instance()->getService<SoundManager>().playMusic("level2", -1);
			}
			else if (state == "level_three")
			{
				ServiceManager::Instance()->getService<SoundManager>().playMusic("level3", -1);
			}
			else if (state == "level_four")
			{
				ServiceManager::Instance()->getService<SoundManager>().playMusic("level4", -1);
			}
		}

	}
	else
	{
		const auto state = ServiceManager::Instance()->getService<StateMachine>().peekState().getStateID();
		if (state != "level_four")
		{
			spawnChance = RandomGenerator{}.getRandomNumber(1, 100);
		}
	}

	if (spawnChance > 96) // chance of 4%; 
	{
		// drop item
		auto& weapon = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		weapon.addComponent<TransformComponent>(killedTransform.position.x, killedTransform.position.y, 48, 32, 1);
		weapon.addComponent<CollisionComponent>("weapon_spawn", killedTransform.position.x, killedTransform.position.y,
		                                        48, 32);

		WeaponFactory wFactory{};
		RandomGenerator generator = RandomGenerator{};
		int const weaponDeterminator = generator.getRandomNumber(1, 10);
		int const level = entity.getComponent<StatsComponent>().getLevel();

		WeaponComponent wComponent = *wFactory.generateWeapon(weaponDeterminator < 6, level - 1,
		                                                      level + 2 <= 10 ? level + 2 : 10, -9, 9);
		weapon.addComponent<WeaponComponent>(wComponent.textureID, wComponent.name, wComponent.isMagic,
		                                     wComponent.power, wComponent.fireDelay, wComponent.bulletTexture,
		                                     wComponent.attackingTextureID);

		weapon.addComponent<SpriteComponent>(weapon.getComponent<WeaponComponent>().textureID.c_str(), 5);
		weapon.addComponent<PickUpComponent>();

		for (const auto& group : entity.getGroups())
		{
			ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(weapon, group);
		}
	}
	else if (spawnChance > 93)
	{
		// chance of 4%
		auto& potion = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		potion.addComponent<TransformComponent>(killedTransform.position.x, killedTransform.position.y, 48, 32, 1);
		potion.addComponent<SpriteComponent>("potion", 5);
		potion.addComponent<CollisionComponent>("healthkit", killedTransform.position.x, killedTransform.position.y, 48,
		                                        32);
		potion.addComponent<PickUpComponent>();
		for (const auto& group : entity.getGroups())
		{
			ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(potion, group);
		}
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
	bloodPuddle.addComponent<SpriteComponent>("blood2", 10);
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
	if (!entity.hasComponent<EnemyMovementComponent>() || entity.hasComponent<ChaseComponent>())
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
}
