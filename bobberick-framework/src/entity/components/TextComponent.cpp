#include "TextComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../FontManager.h"
#include "../../services/RenderService.h"

void TextComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

	sourceRect.x = sourceRect.y = 0;
	destinationRect.w = sourceRect.w = transform->width;
	destinationRect.h = sourceRect.h = transform->height;
	destinationRect.x = transform->position.getX();
	destinationRect.y = transform->position.getY();
}

void TextComponent::update()
{
	sourceRect.x = sourceRect.y = 0;
	destinationRect.w = sourceRect.w = transform->width;
	destinationRect.h = sourceRect.h = transform->height;
	destinationRect.x = transform->position.getX();
	destinationRect.y = transform->position.getY();
}

void TextComponent::render()
{
    ServiceManager::Instance()->getService<FontManager>().draw(texture, &sourceRect, &destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer());
}

TextComponent::TextComponent(const char *path, const char *textureID, const std::string text, int size)
{
    if (ServiceManager::Instance()->getService<FontManager>().load(path, textureID, text, size, ServiceManager::Instance()->getService<RenderService>().renderer)) {
        texture = textureID;
    } else {
        std::cout << SDL_GetError();
    }
}
