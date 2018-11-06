#include "EdgeShapeComponent.h"
#include "../../Entity.h"
#include "../CollisionComponent.h"

void EdgeShapeComponent::init()
{
	collComponent = &entity->getComponent<CollisionComponent>();
}

EdgeShapeComponent::EdgeShapeComponent(b2Vec2 edgeStart, b2Vec2 edgeEnd)
{
	edgeShape.Set(edgeStart, edgeEnd);
	fixtureDef.shape = &edgeShape;
	fixture = collComponent->body->CreateFixture(&fixtureDef);
}

EdgeShapeComponent::~EdgeShapeComponent()
{
	collComponent->body->DestroyFixture(fixture);
}