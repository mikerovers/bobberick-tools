#include "CollisionHelper.h"

bool CollisionHelper::AABB(const SDL_Rect* a, const SDL_Rect* b)
{
    return
        a->x + a->w >= b->x &&
        b->x + b->w >= a->x &&
        a->y + a->h >= b->y &&
        b->y + b->h >= a->y;
}

bool CollisionHelper::AABB(const CollisionComponent &a, const CollisionComponent &b)
{
    return AABB(a.collider, b.collider);
}
