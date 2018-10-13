#include "PolygonShapeComponent.h"
#include "../../Entity.h"
#include "Common/b2BlockAllocator.h"

void PolygonShapeComponent::init()
{
	collComponent = &entity->getComponent<CollisionComponent>();
}

PolygonShapeComponent::PolygonShapeComponent(b2Vec2 vertices[], float32 top, float32 left)
{
	polygonShape.Set(vertices, vertices->Length());
	fixtureDef.shape = &polygonShape;
	fixture = collComponent->body->CreateFixture(&fixtureDef);
}

PolygonShapeComponent::~PolygonShapeComponent()
{
	collComponent->body->DestroyFixture(fixture);
}