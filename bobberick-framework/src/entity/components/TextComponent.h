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
    TextComponent(const char * path, const char* textureID, const std::string text, int size);

    void init() override;
    void update() override;
    void render() override;
private:
    TransformComponent* transform{};
    std::string texture;
    SDL_Rect sourceRect{};
    SDL_Rect destinationRect{};
};


#endif //BOBBERICK_TOOLS_TEXTCOMPONENT_H
