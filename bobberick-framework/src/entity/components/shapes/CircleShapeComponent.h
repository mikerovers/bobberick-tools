#ifndef BOBBERICK_TOOLS_CIRCLESHAPECOMPONENT_H
#define BOBBERICK_TOOLS_CIRCLESHAPECOMPONENT_H

#include "../../Component.h"
#include "Collision/Shapes/b2CircleShape.h"
#include "bobberick-framework/src/entity/components/CollisionComponent.h"
#include "Dynamics/b2Fixture.h"
#include "Common/b2BlockAllocator.h"

class CircleShapeComponent : public Component
{
public:
	CircleShapeComponent(float32 top, float32 left, float32 radius);

	void init() override;
private:
	CollisionComponent* collComponent;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture;

	~CircleShapeComponent();
};


#endif // BOBBERICK_TOOLS_CIRCLESHAPECOMPONENT_H