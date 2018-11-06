#include "RectangleShapeComponent.h"
#include "../../Entity.h"
#include "Common/b2BlockAllocator.h"
#include "../CollisionComponent.h"

void RectangleShapeComponent::init()
{
	collComponent = &entity->getComponent<CollisionComponent>();
}

RectangleShapeComponent::RectangleShapeComponent(float32 halfWidth, float32 halfHeight)
{
	polygonShape.SetAsBox(halfWidth, halfHeight);
	fixtureDef.shape = &polygonShape;
	fixture = collComponent->body->CreateFixture(&fixtureDef);
}

RectangleShapeComponent::~RectangleShapeComponent()
{
	collComponent->body->DestroyFixture(fixture);
}
