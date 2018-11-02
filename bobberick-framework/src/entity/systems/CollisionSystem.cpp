#include "CollisionSystem.h"
#include "../CollisionHelper.h"

CollisionSystem::CollisionSystem(EntityManager &entityManager) : System(entityManager)
{

}

void CollisionSystem::update()
{
    auto* helper = new CollisionHelper();

    for (auto& entity : entityManager.getAllEntitiesWithComponent<CollisionComponent>()) {
        auto& colliderA = entity->getComponent<CollisionComponent>();

        for (auto& otherEntity : entityManager.getAllEntitiesWithComponent<CollisionComponent>()) {
            auto& colliderB = otherEntity->getComponent<CollisionComponent>();
            if (colliderA.tag != colliderB.tag && helper->AABB(colliderA, colliderB)) {
                std::cout << "Collision has happened!" << std::endl;
            }
        }


    }

    delete helper;
}