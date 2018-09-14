#include "DrawSystem.h"
#include "../components/SpriteComponent.h"
#include "../../TextureManager.h"
#include "../../services/ServiceManager.h"

DrawSystem::DrawSystem(EntityManager &entityManager) : System(entityManager)
{
}

void DrawSystem::update()
{
    for (auto& entity : entityManager.getAllEntitiesWithComponent<SpriteComponent>()) {
        auto& tx = ServiceManager::Instance()->getService<TextureManager>();
        auto & spr = entity->getComponent<SpriteComponent>();

        spr.render();
    }
}
