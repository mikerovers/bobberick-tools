#ifndef BOBBERICK_TOOLS_BULLETSYSTEM_H
#define BOBBERICK_TOOLS_BULLETSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class BulletSystem : public System
{
public:
	explicit BulletSystem(EntityManager& entityManager);
	void update() override;
};


#endif //BOBBERICK_TOOLS_BULLETSYSTEM_H
