#include "PlayerMovementSystem.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/services/InputHandler.h"

PlayerMovementSystem::PlayerMovementSystem(EntityManager &entityManager) : System(entityManager)
{

}

void PlayerMovementSystem::update()
{
    for (auto& entity: entityManager->getAllEntitiesWithComponent<PlayerMovementComponent>()) {
        auto& transform = entity->getComponent<TransformComponent>();
        auto& inputService = ServiceManager::Instance()->getService<InputHandler>();


    }
}
