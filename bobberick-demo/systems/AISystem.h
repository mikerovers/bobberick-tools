#ifndef BOBBERICK_TOOLS_AISYSTEM_H
#define BOBBERICK_TOOLS_AISYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class AISystem : public System
{
public:
	explicit AISystem(EntityManager& entityManager);
	void update() override;
	void stopMoving();
};


#endif //BOBBERICK_TOOLS_AISYSTEM_H
