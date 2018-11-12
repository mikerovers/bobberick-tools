#ifndef BOBBERICK_TOOLS_COLLISIONHANDLINGSYSTEM_H
#define BOBBERICK_TOOLS_COLLISIONHANDLINGSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class CollisionHandlingSystem : public System
{
public:
	explicit CollisionHandlingSystem(EntityManager& entityManager);
	void update() override;
	void handlePlayerCollision(std::shared_ptr<Entity> entity);
	void handleAICollision(std::shared_ptr<Entity> entity);
};


#endif //BOBBERICK_TOOLS_COLLISIONHANDLINGSYSTEM_H
