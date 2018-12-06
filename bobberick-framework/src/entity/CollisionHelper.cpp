#include "CollisionHelper.h"

bool CollisionHelper::AABB(const SDL_Rect& a, const SDL_Rect& b)
{
	return SDL_HasIntersection(&a, &b);
}

bool CollisionHelper::AABB(const CollisionComponent &a, const CollisionComponent &b)
{
	return AABB(a.collider, b.collider);
}

int CollisionHelper::AABBDirection(const CollisionComponent &a, const CollisionComponent &b)
{
	int returnValue = 0;
	auto& movingObject = a.collider;
	auto& stationaryObject = b.collider;

	// what side of the stationaryObject does the movingObject collide on?
	bool intersectsTop = false;
	bool intersectsRight = false;

	if (movingObject.x > stationaryObject.x)
		intersectsRight = true;
	// y up is neg
	if (movingObject.y < stationaryObject.y)
		intersectsTop = true;

	// the height & width of the intersection rectangle
	short int height, width;

	if (intersectsTop)
		height = abs(stationaryObject.y - (movingObject.y + movingObject.h));
	else
		height = abs(stationaryObject.y + stationaryObject.h - movingObject.y);
	if (intersectsRight)
		width = abs(stationaryObject.x + stationaryObject.w - movingObject.x);
	else
		width = abs(stationaryObject.x - (movingObject.x + movingObject.w));

	bool const moveInXDirection = height > width;
	// adjust moving object's position accordingly

	if (moveInXDirection)
	{
		if (intersectsRight)
			returnValue += 1;
		else
			returnValue += 2;
	}
	else
	{
		if (intersectsTop)
			returnValue += 4;
		else
			returnValue += 8;
	}
	
	return returnValue;
}
