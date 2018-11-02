#include "PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"

PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager) : System(entityManager)
{

}

void PlayerInputSystem::update()
{
    for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerMovementComponent>()) {
        auto& transform = entity->getComponent<TransformComponent>();
        auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();

//        std::cout << "Joystick x: " << inputHandler.xvalue(0, 1) << std::endl;
//        std::cout << "Joystick y: " << inputHandler.xvalue(0, 1) << std::endl;

        transform.velocity.setX(inputHandler.xvalue(0, 1));
        transform.velocity.setY(inputHandler.yvalue(0, 1));

        auto& collisionComponent = entity->getComponent<CollisionComponent>();
        collisionComponent.collider->x = transform.position.getX();
        collisionComponent.collider->y = transform.position.getY();
        collisionComponent.collider->w = transform.width;
        collisionComponent.collider->h = transform.height;

        transform.update();
    }
}
