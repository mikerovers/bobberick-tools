#include "SpriteComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../TextureManager.h"
#include "../../services/RenderService.h"

void SpriteComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    sourceRect.x = sourceRect.y = 0;
    sourceRect.w = sourceRect.h = 256;
    destinationRect.x = destinationRect.y = 0;
    destinationRect.w = destinationRect.h = 256;
}

void SpriteComponent::update()
{
    destinationRect.x = static_cast<int>(0);
    destinationRect.y = static_cast<int>(0);
    destinationRect.w = 256;
    destinationRect.h = 256;
}

void SpriteComponent::render()
{
    ServiceManager::Instance()->getService<TextureManager>().draw(texture, &sourceRect, &destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer());
}

SpriteComponent::SpriteComponent(const char *path, const char *textureID)
{
    if (ServiceManager::Instance()->getService<TextureManager>().load(path, textureID, ServiceManager::Instance()->getService<RenderService>().renderer)) {
        texture = textureID;
    } else {
        std::cout << SDL_GetError();
    }
}
