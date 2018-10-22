#include "DrawSystem.h"
#include "../components/SpriteComponent.h"
#include "../components/TextComponent.h"
#include "../components/FadeComponent.h"
#include "../../TextureManager.h"
#include "../../FontManager.h"
#include "../../services/ServiceManager.h"

DrawSystem::DrawSystem(EntityManager &entityManager) : System(entityManager)
{
}

void DrawSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<FadeComponent>()) {
		auto& tx = ServiceManager::Instance()->getService<TextureManager>();
		auto & fade = entity->getComponent<FadeComponent>();
		fade.update();
	}

    for (auto& entity : entityManager.getAllEntitiesWithComponent<SpriteComponent>()) {
        auto& tx = ServiceManager::Instance()->getService<TextureManager>();
        auto & spr = entity->getComponent<SpriteComponent>();

		spr.update();
        spr.render();
    }

	for (auto& entity : entityManager.getAllEntitiesWithComponent<TextComponent>()) {
		auto& tx = ServiceManager::Instance()->getService<FontManager>();
		auto & spr = entity->getComponent<TextComponent>();

		spr.render();
	}
}
