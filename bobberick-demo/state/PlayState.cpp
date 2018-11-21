#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../components/StatsComponent.h"
#include "../components/SpawnComponent.h"
#include "../components/ShootComponent.h"
#include "../components/PlayerStatsComponent.h"
#include "../components/InventoryComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../factory/ObjectFactory.h"
#include "../factory/enemies/EnemyFactory.h"
#include "../factory/WeaponFactory.h"

std::string PlayState::getStateID() const
{
	return "playing";
}

void PlayState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool PlayState::onEnter()
{
	makeEnemies();
	auto& player = makePlayer();
	auto& level = makeTileMap();
	makeGui();

	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/arrow-swoosh-2.ogg", "arrow",
	                                                            SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/footsteps_on_gravel.ogg",
	                                                            "footsteps", SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/magical_zap.ogg", "bolt",
	                                                            SOUND_SFX);

	// auto& box = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	// box.addComponent<CollisionComponent>("fire", 140, 175, 40);

	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/level_1.wav", "level1",
	                                                            SOUND_MUSIC);
	ServiceManager::Instance()->getService<SoundManager>().playMusic("level1", -1);

	WeaponFactory().generateWeapon(false, 0, 10, -9, 9); // For testing purposes
	WeaponFactory().generateWeapon(true, 0, 10, -9, 9); // For testing purposes

    instantiateSystems();

	return true;
}

bool PlayState::onExit()
{
	ServiceManager::Instance()->getService<SoundManager>().stopMusic();
	ServiceManager::Instance()->getService<SoundManager>().stopSound(-1);
	std::cout << "Exited playstate" << std::endl;

	return true;
}

bool PlayState::shouldExit()
{
	return _exitPressed;
}

Entity& PlayState::makeTileMap() const
{
	auto& level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(level, getStateID());


	// Use LevelFactory to load and create tilemap components.
	LevelFactory levelFactory;
	const auto tilesetComponent = levelFactory.Load("assets/maps/map2.tmx",
	                                                ServiceManager::Instance()
	                                                ->getService<RenderService>().getRenderer());
	level.addExistingComponent<TilesetComponent>(tilesetComponent);

	ObjectFactory objectFactory;
	for (auto object : level.getComponent<TilesetComponent>().objects)
	{
		auto& objEntity = objectFactory.getObject(object);
		ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(objEntity, getStateID());
	}

	return level;
}

Entity& PlayState::makePlayer() const
{
	auto& player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	player.addComponent<TransformComponent>(100, 100, 64, 32, 1);
	auto& spriteComponent = player.addComponent<SpriteComponent>("assets/image/character/character.png", "character", 6,
	                                                             4, 5);
	spriteComponent.addTexture("assets/image/character/character_casting.png", "character_casting");
	spriteComponent.addTexture("assets/image/character/character_shooting.png", "character_shooting");
	spriteComponent.addTexture("assets/image/character/character_shield.png", "character_shield");
	player.addComponent<PlayerMovementComponent>();

	// 3 seconds (180 ticks) of shield mode, 3/10ths of a second recovered per second.
	player.addComponent<PlayerStatsComponent>(new StatsComponent(100000, 100000, 1, 3, 1, 1), 180, 180, 0.3, 0, 0);

	player.addComponent<TimerComponent>();
	player.addComponent<ShootComponent>();
	player.addComponent<CollisionComponent>("player");
	player.addComponent<InventoryComponent>(&player.getComponent<PlayerStatsComponent>());
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(player, getStateID());

	return player;
}

void PlayState::instantiateSystems() const
{
	for (const auto& system : systems)
	{
		system->init();
	}
}

void PlayState::makeEnemies() const
{
	EnemyFactory enemyFactory = EnemyFactory{};
	for (auto x = 0; x < 5; x++)
	{
		for (auto y = 0; y < 5; y++)
		{
			auto& enemy = enemyFactory.getRandomEnemy(1, 4);
			ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(enemy, getStateID());

			auto& enemyTransform = enemy.getComponent<TransformComponent>();
			enemyTransform.position.x = 50 + 10 * x;
			enemyTransform.position.y = 350 + 10 * y;
		}
	}
	/*auto& enemy = enemyFactory.getBoss(10);
	auto& enemyTransform = enemy.getComponent<TransformComponent>();
	enemyTransform.position.x = 250 + 50;
	enemyTransform.position.y = 250;
*/
	auto& manufacturer = enemyFactory.getEnemy(3, "manufacturer");
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(manufacturer, getStateID());

	auto& manufacturerTransform = manufacturer.getComponent<TransformComponent>();
	auto& manufacturerSpawn = manufacturer.getComponent<SpawnComponent>();
	manufacturerSpawn.type = "orc";
	manufacturerSpawn.spawnTimer = 1000;
	manufacturerSpawn.maxCount = 20;
	manufacturerTransform.position.x = 500;
	manufacturerTransform.position.y = 300;

	auto& manufacturer2 = enemyFactory.getEnemy(3, "manufacturer");
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(manufacturer2, getStateID());

	auto& manufacturer2Transform = manufacturer2.getComponent<TransformComponent>();
	auto& manufacturerSpawn2 = manufacturer2.getComponent<SpawnComponent>();
	manufacturerSpawn2.type = "fireWizard";
	manufacturerSpawn2.spawnTimer = 2500;
	manufacturerSpawn2.maxCount = 10;
	manufacturer2Transform.position.x = 500;
	manufacturer2Transform.position.y = 250;
}

void PlayState::makeGui()
{
	auto& exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());


	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		std::cout << "Exit button clicked." << std::endl;
		_exitPressed = true;
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	auto* exitButtonTransformComponent = new TransformComponent();
	exitButtonTransformComponent->position.x = 10;
	exitButtonTransformComponent->position.y = 60;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("assets/image/button/exitbutton.png", "exitbutton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
}
