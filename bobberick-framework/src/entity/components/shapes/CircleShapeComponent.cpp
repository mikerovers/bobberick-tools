#include "CircleShapeComponent.h"
#include "../../Entity.h"
#include "Common/b2BlockAllocator.h"
#include "../CollisionComponent.h"

void CircleShapeComponent::init()
{
	collComponent = &entity->getComponent<CollisionComponent>();
}

CircleShapeComponent::CircleShapeComponent(float32 top, float32 left, float32 radius)
{
	circleShape.m_p.Set(top, left);
	circleShape.m_radius = radius;
	fixtureDef.shape = &circleShape;
	fixture = collComponent->body->CreateFixture(&fixtureDef);
}

CircleShapeComponent::~CircleShapeComponent()
{
	collComponent->body->DestroyFixture(fixture);
}