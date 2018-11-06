#ifndef BOBBERICK_TOOLS_RECTANGLESHAPECOMPONENT_H
#define BOBBERICK_TOOLS_RECTANGLESHAPECOMPONENT_H

#include "../../Component.h"
#include "Collision/Shapes/b2PolygonShape.h"
#include "../CollisionComponent.h"
#include "Dynamics/b2Fixture.h"
#include "Common/b2BlockAllocator.h"

class RectangleShapeComponent : public Component
{
public:
	RectangleShapeComponent(float32 halfWidth, float32 halfHeight);

	void init() override;
private:
	CollisionComponent* collComponent;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture;
	
	~RectangleShapeComponent();
};

#endif // BOBBERICK_TOOLS_RECTANGLESHAPECOMPONENT_H