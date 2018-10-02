#include "TextComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../FontManager.h"
#include "../../services/RenderService.h"

void TextComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    sourceRect.x = sourceRect.y = 0;
    sourceRect.w = sourceRect.h = 256;
    destinationRect.x = destinationRect.y = 0;
    destinationRect.w = destinationRect.h = 256;
}

void TextComponent::update()
{
    destinationRect.x = static_cast<int>(0);
    destinationRect.y = static_cast<int>(0);
    destinationRect.w = 256;
    destinationRect.h = 256;
}

void TextComponent::render()
{
    ServiceManager::Instance()->getService<FontManager>().draw(texture, &sourceRect, &destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer());
}

TextComponent::TextComponent(const char *path, const char *textureID, const char* text, int size)
{
    if (ServiceManager::Instance()->getService<FontManager>().load(path, textureID, text, size, ServiceManager::Instance()->getService<RenderService>().renderer)) {
        texture = textureID;
    } else {
        std::cout << SDL_GetError();
    }
}
