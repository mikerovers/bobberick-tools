#include "TextComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../services/FontManager.h"
#include "../../services/RenderService.h"

void TextComponent::setText(std::string newText) {
	if (newText != text) { // Some text may 'update' every frame, but we won't unneccessarily create a new text surface.
		if (ServiceManager::Instance()->getService<FontManager>().createText(font, texture, newText, ServiceManager::Instance()->getService<RenderService>().renderer)) {
			text = newText;
		} else {
			std::cout << SDL_GetError();
		}
	}
}

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
    ServiceManager::Instance()->getService<TextureManager>().draw(texture, &sourceRect, &destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer(), false);
}

TextComponent::TextComponent(const char *fontID, const char *textureID, const std::string text)
{
	font = fontID;
	TextComponent::text = text;
    if (ServiceManager::Instance()->getService<FontManager>().createText(fontID, textureID, text, ServiceManager::Instance()->getService<RenderService>().renderer)) {
        texture = textureID;
    } else {
        std::cout << SDL_GetError();
    }
}
