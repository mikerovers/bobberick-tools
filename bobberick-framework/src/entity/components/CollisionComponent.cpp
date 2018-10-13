#include "CollisionComponent.h"
#include "../Entity.h"
#include "bobberick-framework/src/services/ServiceManager.h"
#include "bobberick-framework/src/services/WorldService.h"

void CollisionComponent::init()
{
	transform = &entity->getComponent<TransformComponent>();
	posX = transform->position.getX();
	posY = transform->position.getY();

	world = ServiceManager::Instance()->getService<WorldService>().getWorld();
}

CollisionComponent::CollisionComponent(/*b2World &worldRef, */b2BodyType type)
{
	//world = &worldRef;
	//world = new b2World(b2Vec2(0, 0)); // No gravity

	bodyDef.type = type;
	bodyDef.position.Set(posX, posY);
}

CollisionComponent::CollisionComponent(/*b2World &worldRef, */b2BodyType type, float angle)
{
	//world = &worldRef;

	bodyDef.type = type;
	bodyDef.position.Set(posX, posY);
	bodyDef.angle = angle;

	body = world->CreateBody(&bodyDef);
}

CollisionComponent::~CollisionComponent()
{
	world->DestroyBody(body);
}
