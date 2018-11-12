#ifndef BOBBERICK_TOOLS_COLLISIONCOMPONENT_H
#define BOBBERICK_TOOLS_COLLISIONCOMPONENT_H


#include <SDL_rect.h>
#include <string>
#include <SDL_system.h>
#include "TransformComponent.h"
#include "../Entity.h"

class CollisionComponent : public Component
{
public:
    SDL_Rect* collider;
    std::string tag;

    std::string texture;
    SDL_Rect sourceRect{};
    SDL_Rect destinationRect{};

    CollisionComponent(std::string tag);
    CollisionComponent(std::string tag, int xPos, int yPos, int size);
    CollisionComponent(std::string tag, int xPos, int yPos, int height, int width);

    void init() override;
};


#endif //BOBBERICK_TOOLS_COLLISIONCOMPONENT_H
