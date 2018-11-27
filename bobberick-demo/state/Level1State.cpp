#include "Level1State.h"
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
#include "../components/PlayerComponent.h"
#include "../components/InventoryComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../factory/ObjectFactory.h"
#include "../factory/enemies/EnemyFactory.h"
#include "../factory/WeaponFactory.h"

std::string Level1State::getStateID() const
{
	return "playing";
}

void Level1State::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool Level1State::onEnter()
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

	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/level_1.wav", "level1",
		SOUND_MUSIC);
	ServiceManager::Instance()->getService<SoundManager>().playMusic("level1", -1);

	WeaponFactory().generateWeapon(false, 0, 10, -9, 9); // For testing purposes
	WeaponFactory().generateWeapon(true, 0, 10, -9, 9); // For testing purposes

	instantiateSystems();

	return true;
}

bool Level1State::onExit()
{
	std::cout << "Exited playstate" << std::endl;
	ServiceManager::Instance()->getService<SoundManager>().stopMusic();
	ServiceManager::Instance()->getService<SoundManager>().stopAllSounds();

	return true;
}

bool Level1State::shouldExit()
{
	return _exitPressed;
}

Entity& Level1State::makeTileMap() const
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

Entity& Level1State::makePlayer() const
{
	auto& player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	player.addComponent<TransformComponent>(100, 100, 64, 32, 1);
	auto& spriteComponent = player.addComponent<SpriteComponent>("character", 6,
		4, 5);
	player.addComponent<PlayerMovementComponent>();

	// 3 seconds (180 ticks) of shield mode, 3/10ths of a second recovered per second.
	player.addComponent<PlayerComponent>();

	player.addComponent<TimerComponent>();
	player.addComponent<ShootComponent>();
	player.addComponent<CollisionComponent>("player");
	//player.addComponent<InventoryComponent>(&player.getComponent<PlayerComponent>());
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(player, getStateID());

	return player;
}

void Level1State::instantiateSystems() const
{
	for (const auto& system : systems)
	{
		system->init();
	}
}

void Level1State::makeEnemies() const
{
	EnemyFactory enemyFactory = EnemyFactory{};
	for (auto x = 0; x < 3; x++)
	{
		for (auto y = 0; y < 3; y++)
		{
			auto& enemy = enemyFactory.getRandomEnemy(1, 4);
			ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(enemy, getStateID());

			auto& enemyTransform = enemy.getComponent<TransformComponent>();
			enemyTransform.position.x = 50 + 25 * x;
			enemyTransform.position.y = 350 + 25 * y;
		}
	}
}

void Level1State::makeGui()
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
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
}
