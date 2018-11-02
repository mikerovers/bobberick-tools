#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"

std::string PlayState::getStateID() const
{
    return "playing";
}

void PlayState::update()
{
    for (const auto &system : systems) {
        system->update();
    }
}

bool PlayState::onEnter()
{
    std::cout << "Entered playstate" << std::endl;

    std::shared_ptr<Entity> player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    player->addComponent<TransformComponent>();
    player->addComponent<SpriteComponent>("assets/image/spritestrip.png", "character");
    player->addComponent<PlayerMovementComponent>();
    player->addComponent<CollisionComponent>("player");

    std::shared_ptr<Entity> level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* factory = new LevelFactory();
    TilesetComponent* tilesetComponent = factory->Load("assets/maps/map1.tmx", ServiceManager::Instance()->getService<RenderService>().getRenderer());
    level->addExistingComponent<TilesetComponent>(tilesetComponent);

    std::shared_ptr<Entity> box = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* collisionComponent = new CollisionComponent("test", 0, 0, 40);
    box->addExistingComponent<CollisionComponent>(collisionComponent);

    delete factory;

    return true;
}

bool PlayState::onExit()
{
    std::cout << "Exited playstate" << std::endl;

    return true;
}

bool PlayState::shouldExit()
{
    return false;
}
