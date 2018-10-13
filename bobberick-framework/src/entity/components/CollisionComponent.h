#ifndef BOBBERICK_TOOLS_COLLISIONCOMPONENT_H
#define BOBBERICK_TOOLS_COLLISIONCOMPONENT_H

#include "../Component.h"
#include "Dynamics/b2World.h"
#include "Dynamics/b2Body.h"
#include "TransformComponent.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent() = default;
	CollisionComponent(/*b2World& worldRef, */b2BodyType type);
	CollisionComponent(/*b2World& worldRef, */b2BodyType type, float angle);

	b2Body* body;

	void init() override;
private:
	TransformComponent* transform;
	b2World* world;
	b2BodyDef bodyDef;
	float posX;
	float posY;

	~CollisionComponent();
};

#endif // BOBBERICK_TOOLS_COLLISIONCOMPONENT_H