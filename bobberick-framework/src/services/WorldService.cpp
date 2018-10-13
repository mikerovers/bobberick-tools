#include "WorldService.h"
#include "Common/b2Math.h"

void WorldService::init()
{
	
}

b2World* WorldService::getWorld()
{
	return world;
}

WorldService::WorldService()
{
	world = new b2World(b2Vec2(0, 0));
}