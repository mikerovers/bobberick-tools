#include "Level2State.h"
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

void Level2State::update()
{
    for (const auto& system : systems)
    {
		if (exiting)
			break;

        system->update();
    }
}

bool Level2State::onEnter()
{
    ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/arrow-swoosh-2.ogg", "arrow",
                                                                SOUND_SFX);
    ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/footsteps_on_gravel.ogg",
                                                                "footsteps", SOUND_SFX);
    ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/magical_zap.ogg", "bolt",
                                                                SOUND_SFX);

    ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/level_2.wav", "level2",
                                                                SOUND_MUSIC);
	ServiceManager::Instance()->getService<SoundManager>().playMusic("level2", -1);

    auto& level = makeTileMap();
    makePlayer();

    for (const auto& system : systems)
    {
        system->init();
    }

    return true;
}

bool Level2State::onExit()
{
	ServiceManager::Instance()->getService<SoundManager>().stopMusic();
	ServiceManager::Instance()->getService<SoundManager>().stopAllSounds();
    return true;
}

bool Level2State::shouldExit()
{
    return false;
}

std::string Level2State::getStateID() const
{
    return "level_two";
}

Entity &Level2State::makeTileMap() const
{
    auto& level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(level, getStateID());


    // Use LevelFactory to load and create tilemap components.
    LevelFactory levelFactory;
    const auto tilesetComponent = levelFactory.Load("assets/maps/map3.tmx",
                                                    ServiceManager::Instance()
                                                            ->getService<RenderService>().getRenderer());
    level.addExistingComponent<TilesetComponent>(tilesetComponent);

    ObjectFactory objectFactory;
    for (auto object : level.getComponent<TilesetComponent>().objects)
    {
        auto& objEntity = objectFactory.getObject(object);
        ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(objEntity, getStateID());
		if (objEntity.hasComponent<SpawnComponent>()) {
			auto& spawnComponent = objEntity.getComponent<SpawnComponent>();
			spawnComponent.maxCount *= 3;
		}
		if (objEntity.hasComponent<SpawnComponent>()) {
			objEntity.getComponent<StatsComponent>().changeLevel(3);
		}
    }


    return level;
}

void Level2State::makePlayer() const
{
    for(auto& p : ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<PlayerComponent>()) {
        ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(*p, getStateID());
    }
}
