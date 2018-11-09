#ifndef BOBBERICK_TOOLS_COLLISIONCOMPONENT_H
#define BOBBERICK_TOOLS_COLLISIONCOMPONENT_H


#include <SDL_rect.h>
#include <string>
#include <SDL_system.h>
#include "TransformComponent.h"
#include "../Entity.h"
#include <vector>


class CollisionComponent : public Component
{
public:
    SDL_Rect* collider;
    std::string tag;

    std::string texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;

    CollisionComponent(std::string tag);
    CollisionComponent(std::string tag, int xPos, int yPos, int size);

	std::vector<Entity*> collidingWith;

    void init() override;
};


#endif //BOBBERICK_TOOLS_COLLISIONCOMPONENT_H
