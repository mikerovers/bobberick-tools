#include "DrawSystem.h"
#include "../components/SpriteComponent.h"
#include "../components/TextComponent.h"
#include "../../TextureManager.h"
#include "../../FontManager.h"
#include "../../services/ServiceManager.h"
#include "../components/TileSetComponent.h"
#include "../../services/RenderService.h"

DrawSystem::DrawSystem(EntityManager &entityManager) : System(entityManager)
{
}

void DrawSystem::update()
{
    auto& tx = ServiceManager::Instance()->getService<TextureManager>();
    auto& rs = ServiceManager::Instance()->getService<RenderService>();

    for (auto& entity : entityManager.getAllEntitiesWithComponent<SpriteComponent>()) {
        auto & spr = entity->getComponent<SpriteComponent>();

		spr.update();
        spr.render();
    }

    for (auto& entity : entityManager.getAllEntitiesWithComponent<TileSetComponent>()) {
        auto& tileSetComponent = entity->getComponent<TileSetComponent>();

        for (auto& tile: tileSetComponent.tiles) {
            std::unique_ptr<SDL_Rect> s = std::make_unique<SDL_Rect>(tile->getSourceRect());
            std::unique_ptr<SDL_Rect> d = std::make_unique<SDL_Rect>(tile->getDestinationRect());

            tx.draw("mountain_landscape", s.get(), d.get(), rs.getRenderer());
        }
    }
}
