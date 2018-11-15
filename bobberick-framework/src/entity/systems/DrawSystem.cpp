#include "DrawSystem.h"
#include "../components/SpriteComponent.h"
#include "../components/RectangleComponent.h"
#include "../components/TextComponent.h"
#include "../components/FadeComponent.h"
#include "../../services/TextureManager.h"
#include "../../services/RectangleManager.h"
#include "../../services/FontManager.h"
#include "../../services/ServiceManager.h"
#include "../components/TilesetComponent.h"
#include "../../services/RenderService.h"
#include "../../../../bobberick-framework/src/entity/components/CollisionComponent.h"

DrawSystem::DrawSystem(EntityManager &entityManager) : System(entityManager)
{
}

void DrawSystem::update()
{
	auto& tx = ServiceManager::Instance()->getService<TextureManager>();
	auto& rs = ServiceManager::Instance()->getService<RenderService>();

	for (auto& entity: entityManager.getAllEntitiesWithComponent<TilesetComponent>()) {
		auto& tileSetComponent = entity->getComponent<TilesetComponent>();

		for (auto& tile : tileSetComponent.tiles) {
			std::unique_ptr<SDL_Rect> s = std::make_unique<SDL_Rect>(tile->getSourceRect());
			std::unique_ptr<SDL_Rect> d = std::make_unique<SDL_Rect>(tile->getDestinationRect());

			tx.draw("mountain_landscape", s.get(), d.get(), rs.getRenderer(), false);
		}
	}

	for (auto& entity : entityManager.getAllEntitiesWithComponent<FadeComponent>()) {
		auto & fade = entity->getComponent<FadeComponent>();
		fade.update();
	}

	// Draw in-game sprites under the GUI.
    for (auto& entity : entityManager.getAllEntitiesWithComponent<SpriteComponent>()) {
		if (!entity->getComponent<SpriteComponent>().guiLayer) {
			auto & spr = entity->getComponent<SpriteComponent>();

			spr.update();
			spr.render();
		} 
    }

	for (auto& entity : entityManager.getAllEntitiesWithComponent<RectangleComponent>()) {
		auto & spr = entity->getComponent<RectangleComponent>();

		spr.update();
		spr.render();
	}

	for (auto& entity : entityManager.getAllEntitiesWithComponent<TextComponent>()) {
		auto & spr = entity->getComponent<TextComponent>();

		spr.update();
		spr.render();
	}

	for (auto& entity : entityManager.getAllEntitiesWithComponent<CollisionComponent>()) {
		auto& comp = entity->getComponent<CollisionComponent>();

		auto* sourceRect = new SDL_Rect;
		sourceRect->x = 0;
		sourceRect->y = 0;
		sourceRect->w = 32;
		sourceRect->h = 32;
		auto* destRect = new SDL_Rect;
		destRect->x = comp.collider.x;
		destRect->y = comp.collider.y;
		destRect->w = comp.collider.w;
		destRect->h = comp.collider.h;
		tx.draw("collision", sourceRect, destRect, rs.getRenderer(), false);

		delete sourceRect;
		delete destRect;
	}

	// Draw sprites on top of the GUI.
	for (auto& entity : entityManager.getAllEntitiesWithComponent<SpriteComponent>()) {
		if (entity->getComponent<SpriteComponent>().guiLayer) {
			auto & spr = entity->getComponent<SpriteComponent>();

			spr.update();
			spr.render();
		}
	}
}
