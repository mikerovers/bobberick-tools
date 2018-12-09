#include "ObjectFactory.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/ShootComponent.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../components/PickUpComponent.h"
#include "../components/ItemComponent.h"
#include "../../bobberick-framework/src/util/RandomGenerator.h"
#include "../components/WeaponComponent.h"
#include "WeaponFactory.h"
#include "../components/InventoryComponent.h"

Entity& ObjectFactory::getObject(const TileObject* object)
{
	if (object->name == "healthkit")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, 48, 32, 1);
		entity.addComponent<SpriteComponent>("potion", 5);
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y, 48,
		                                        32);
		entity.addComponent<PickUpComponent>();

		return entity;
	}

	if (object->name == "weapon_spawn")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, 48, 32, 1);
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y, 48, 32);


		WeaponFactory wFactory{};
		RandomGenerator generator = RandomGenerator{};
		int const weaponDeterminator = generator.getRandomNumber(1, 10);

		if (weaponDeterminator < 6)
		{
			// Weapon is a magic weapon
			WeaponComponent wComponent = *wFactory.generateWeapon(true, 1, 10, -7, 7);
			entity.addComponent<WeaponComponent>(wComponent.textureID, wComponent.name, wComponent.isMagic, wComponent.power, wComponent.fireDelay, wComponent.bulletTexture, wComponent.attackingTextureID);
		}
		else
		{
			// Weapon is a non-magic weapon
			WeaponComponent wComponent = *wFactory.generateWeapon(false, 1, 10, -7, 7);
			entity.addComponent<WeaponComponent>(wComponent.textureID, wComponent.name, wComponent.isMagic, wComponent.power, wComponent.fireDelay, wComponent.bulletTexture, wComponent.attackingTextureID);
		}

		entity.addComponent<SpriteComponent>(entity.getComponent<WeaponComponent>().textureID.c_str(), 5);
		entity.addComponent<PickUpComponent>();

		return entity;
	}

	if (object->name == "water")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, object->aabb.height,
		                                        object->aabb.width, 1);
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y,
		                                        object->aabb.height, object->aabb.width);

		return entity;
	}	
	
	if (object->name == "aabb_rectangle")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, object->aabb.height,
		                                        object->aabb.width, 1);
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y,
		                                        object->aabb.height, object->aabb.width);

		return entity;
	}

	if (object->name == "orc_spawner")
	{
		auto& manufacturer = enemyFactory->getEnemy(3, "manufacturer");
		auto& manufacturerTransform = manufacturer.getComponent<TransformComponent>();
		auto& manufacturerSpawn = manufacturer.getComponent<SpawnComponent>();
		manufacturerSpawn.type = "orc";
		manufacturerSpawn.spawnTimer = 100;
		manufacturerSpawn.maxCount = 10;
		manufacturerTransform.position.x = object->position->x;
		manufacturerTransform.position.y = object->position->y;

		return manufacturer;
	}

    if (object->name == "firewizard_spawner")
    {
        auto& manufacturer = enemyFactory->getEnemy(3, "manufacturer");
        auto& manufacturerTransform = manufacturer.getComponent<TransformComponent>();
        auto& manufacturerSpawn = manufacturer.getComponent<SpawnComponent>();
        manufacturerSpawn.type = "fireWizard";
        manufacturerSpawn.spawnTimer = 200;
        manufacturerSpawn.maxCount = 10;
        manufacturerTransform.position.x = object->position->x;
        manufacturerTransform.position.y = object->position->y;

        return manufacturer;
    }

    if (object->name == "chicken_spawner")
    {
        auto& manufacturer = enemyFactory->getEnemy(3, "manufacturer");
        auto& manufacturerTransform = manufacturer.getComponent<TransformComponent>();
        auto& manufacturerSpawn = manufacturer.getComponent<SpawnComponent>();
        manufacturerSpawn.type = "chicken";
        manufacturerSpawn.spawnTimer = 60;
        manufacturerSpawn.maxCount = 20;
        manufacturerTransform.position.x = object->position->x;
        manufacturerTransform.position.y = object->position->y;

        return manufacturer;
    }

    if (object->name == "player_spawn")
	{
		auto& player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		player.addComponent<TransformComponent>(object->position->x, object->position->y, 64, 32, 1);
		auto& spriteComponent = player.addComponent<SpriteComponent>("character", 6,
																	 4, 5, 3);
		player.addComponent<PlayerMovementComponent>();

		// 3 seconds (180 ticks) of shield mode, 3/10ths of a second recovered per second.
		player.addComponent<PlayerComponent>();

		player.addComponent<TimerComponent>();
		player.addComponent<ShootComponent>();
		player.addComponent<CollisionComponent>("player");
		player.addComponent<InventoryComponent>();

		return player;
	}

	return *new Entity();
}

ObjectFactory::ObjectFactory()
{
	enemyFactory = std::make_unique<EnemyFactory>();
}
