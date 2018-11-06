#ifndef BOBBERICK_TOOLS_POLYGONSHAPECOMPONENT_H
#define BOBBERICK_TOOLS_POLYGONSHAPECOMPONENT_H

#include "../../Component.h"
#include "Collision/Shapes/b2PolygonShape.h"
#include "Common/b2Math.h"
#include "../CollisionComponent.h"
#include "Dynamics/b2Fixture.h"
#include "Common/b2BlockAllocator.h"

class PolygonShapeComponent : public Component
{
public:
	PolygonShapeComponent(b2Vec2 vertices[], float32 top, float32 left);

	void init() override;
private:
	CollisionComponent* collComponent;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture;

	~PolygonShapeComponent();
};

#endif // BOBBERICK_TOOLS_POLYGONSHAPECOMPONENT_H