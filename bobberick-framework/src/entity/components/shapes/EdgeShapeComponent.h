#ifndef BOBBERICK_TOOLS_EDGESHAPECOMPONENT_H
#define BOBBERICK_TOOLS_EDGESHAPECOMPONENT_H

#include "../../Component.h"
#include "Collision/Shapes/b2EdgeShape.h"
#include "Common/b2Math.h"
#include "bobberick-framework/src/entity/components/CollisionComponent.h"
#include "Dynamics/b2Fixture.h"

class EdgeShapeComponent : public Component
{
public:
	EdgeShapeComponent(b2Vec2 edgeStart, b2Vec2 edgeEnd);

	void init() override;
private:
	CollisionComponent* collComponent;
	b2EdgeShape edgeShape;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture;

	~EdgeShapeComponent();
};

#endif // BOBBERICK_TOOLS_EDGESHAPECOMPONENT_H