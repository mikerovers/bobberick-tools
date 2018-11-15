#ifndef BOBBERICK_TOOLS_COLLISIONHELPER_H
#define BOBBERICK_TOOLS_COLLISIONHELPER_H

#include <SDL_rect.h>
#include "components/CollisionComponent.h"

class CollisionHelper
{
public:
    bool AABB(const SDL_Rect* a, const SDL_Rect* b);
    bool AABB(const CollisionComponent& a, const CollisionComponent& b);
};


#endif //BOBBERICK_TOOLS_COLLISIONHELPER_H
