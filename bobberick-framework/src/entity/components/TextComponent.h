#ifndef BOBBERICK_TOOLS_TEXTCOMPONENT_H
#define BOBBERICK_TOOLS_TEXTCOMPONENT_H

#include <SDL.h>
#include <string>
#include "../Component.h"
#include "TransformComponent.h"

class TextComponent : public Component
{
public:
    TextComponent() = default;
	TextComponent(const char *fontID, const char *textureID, const std::string text);

	void setText(std::string newText);

    void init() override;
    void update() override;
    void render() override;
private:
    TransformComponent* transform{};
	std::string font; // The fontID from FontManager to use.
    std::string texture; // The textureID from TextureManager to draw to.
	std::string text; // The text to draw.
    SDL_Rect sourceRect{};
    SDL_Rect destinationRect{};
};


#endif //BOBBERICK_TOOLS_TEXTCOMPONENT_H
