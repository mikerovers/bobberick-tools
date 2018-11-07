#ifndef BOBBERICK_TOOLS_SHIELDSYSTEM_H
#define BOBBERICK_TOOLS_SHIELDSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class ShieldSystem : public System
{
public:
	explicit ShieldSystem(EntityManager& entityManager);
	void update() override;
};


#endif //BOBBERICK_TOOLS_SHIELDSYSTEM_H
