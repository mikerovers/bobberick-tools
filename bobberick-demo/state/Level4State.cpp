#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/entity/components/TilesetComponent.h"
#include "../factory/ObjectFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../components/SpawnComponent.h"
#include "../factory/enemies/EnemyFactory.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../components/PlayerMovementComponent.h"
#include "../components/StatsComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/SpawnComponent.h"
#include "../components/ShootComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../components/InventoryComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "Level4State.h"
#include "../services/PlayerStatsService.h"
#include "../components/SpawnMinionsSpellComponent.h"
#include "../components/EndBossComponent.h"
#include "../components/SprayComponent.h"
#include "../../bobberick-framework/src/services/FrameHandler.h"

void Level4State::update()
{
	for (auto& boss : ServiceManager::Instance()
	                  ->getService<EntityManager>().getAllEntitiesWithComponent<EndBossComponent>())
	{
		if (boss->hasComponent<TimerComponent>() && boss->getComponent<TimerComponent>().isTimerFinished())
		{
			boss->getComponent<TransformComponent>().position = spawnPoints[random.getRandomNumber(
				0, spawnPoints.size() -1)];

		}
	}

	for (const auto& system : systems)
	{
		if (!exiting)
		{
			system->update();
		}
		else
		{
			break;
		}
	}
}

bool Level4State::onEnter()
{
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/arrow-swoosh-2.ogg", "arrow",
	                                                            SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/footsteps_on_gravel.ogg",
	                                                            "footsteps", SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/magical_zap.ogg", "bolt",
	                                                            SOUND_SFX);

	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/level_4.wav", "level4",
	                                                            SOUND_MUSIC);
	ServiceManager::Instance()->getService<SoundManager>().playMusic("level4", -1);

	spawnPoints.emplace_back(200, 200);
	spawnPoints.emplace_back(200, 600);
	spawnPoints.emplace_back(600, 600);
	spawnPoints.emplace_back(600, 200);

	auto& level = makeTileMap();
	makePlayer();

	EnemyFactory enemyFactory{};

	auto& boss = enemyFactory.getEnemy(100, "chicken");
	boss.getComponent<TransformComponent>().setScale(1);
	boss.getComponent<TransformComponent>().position = Vector2D{600, 600};
	boss.addComponent<EndBossComponent>();
	boss.addComponent<SprayComponent>();
	boss.addComponent<TimerComponent>();
	boss.getComponent<SprayComponent>().sprayTimer = 1000;

	for (const auto& system : systems)
	{
		system->init();
	}

	return true;
}

bool Level4State::onExit()
{
	ServiceManager::Instance()->getService<SoundManager>().stopMusic();
	ServiceManager::Instance()->getService<SoundManager>().stopAllSounds();
	return true;
}

bool Level4State::shouldExit()
{
	return false;
}

std::string Level4State::getStateID() const
{
	return "level_four";
}

Entity& Level4State::makeTileMap() const
{
	auto& level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(level, getStateID());


	// Use LevelFactory to load and create tilemap components.
	LevelFactory levelFactory;
	const auto tilesetComponent = levelFactory.Load("assets/maps/map5.tmx",
	                                                ServiceManager::Instance()
	                                                ->getService<RenderService>().getRenderer());
	level.addExistingComponent<TilesetComponent>(tilesetComponent);

	ObjectFactory objectFactory(2);
	for (auto object : level.getComponent<TilesetComponent>().objects)
	{
		auto& objEntity = objectFactory.getObject(object);
		ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(objEntity, getStateID());
	}


	return level;
}

void Level4State::makePlayer() const
{
	for (auto& p : ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<PlayerComponent
	     >())
	{
		ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(*p, getStateID());
	}
}
