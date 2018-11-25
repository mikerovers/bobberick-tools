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
#include "../components/PlayerStatsComponent.h"
#include "../components/ShootComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../components/InventoryComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"

void Level2State::update()
{
    for (const auto& system : systems)
    {
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

    ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/level_1.wav", "level1",
                                                                SOUND_MUSIC);
    ServiceManager::Instance()->getService<SoundManager>().playMusic("level1", -1);

    auto& level = makeTileMap();
    makeEnemies();
    makePlayer();

    for (const auto& system : systems)
    {
        system->init();
    }

    return true;
}

bool Level2State::onExit()
{
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
    }

    return level;
}

void Level2State::makeEnemies() const
{
    EnemyFactory enemyFactory = EnemyFactory{};

    auto& manufacturer = enemyFactory.getEnemy(3, "manufacturer");
    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(manufacturer, getStateID());

    auto& manufacturerTransform = manufacturer.getComponent<TransformComponent>();
    auto& manufacturerSpawn = manufacturer.getComponent<SpawnComponent>();
    manufacturerSpawn.type = "fireWizard";
    manufacturerSpawn.spawnTimer = 1000;
    manufacturerSpawn.maxCount = 20;
    manufacturerTransform.position.x = 500;
    manufacturerTransform.position.y = 300;

    auto& manufacturer2 = enemyFactory.getEnemy(3, "manufacturer");
    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(manufacturer2, getStateID());

    auto& manufacturer2Transform = manufacturer2.getComponent<TransformComponent>();
    auto& manufacturerSpawn2 = manufacturer2.getComponent<SpawnComponent>();
    manufacturerSpawn2.type = "fireWizard";
    manufacturerSpawn2.spawnTimer = 100;
    manufacturerSpawn2.maxCount = 10;
    manufacturer2Transform.position.x = 200;
    manufacturer2Transform.position.y = 200;
}

void Level2State::makePlayer() const
{
    auto& player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    player.addComponent<TransformComponent>(100, 100, 64, 32, 1);
    auto& spriteComponent = player.addComponent<SpriteComponent>("character", 6,
                                                                 4, 5);
    player.addComponent<PlayerMovementComponent>();

    // 3 seconds (180 ticks) of shield mode, 3/10ths of a second recovered per second.
    player.addComponent<PlayerStatsComponent>(new StatsComponent(100000, 100000, 1, 3, 1, 1), 180, 180, 0.3, 0, 0);

    player.addComponent<TimerComponent>();
    player.addComponent<ShootComponent>();
    player.addComponent<CollisionComponent>("player");
    player.addComponent<InventoryComponent>(&player.getComponent<PlayerStatsComponent>());
    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(player, getStateID());
}