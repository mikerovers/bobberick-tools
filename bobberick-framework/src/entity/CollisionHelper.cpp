#include "CollisionHelper.h"

bool CollisionHelper::AABB(const SDL_Rect* a, const SDL_Rect* b)
{
	return SDL_HasIntersection(a, b);
}

bool CollisionHelper::AABB(const CollisionComponent &a, const CollisionComponent &b)
{
    return AABB(a.collider, b.collider);
}
