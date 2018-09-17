#ifndef BOBBERICK_TOOLS_SPRITECOMPONENT_H
#define BOBBERICK_TOOLS_SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include <string>
#include "../Component.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent() = default;
    SpriteComponent(const char * path, const char* textureID);

    void init() override;
    void update() override;
    void render() override;
private:
    TransformComponent* transform{};
    std::string texture;
    SDL_Rect sourceRect{};
    SDL_Rect destinationRect{};
};


#endif //BOBBERICK_TOOLS_SPRITECOMPONENT_H
