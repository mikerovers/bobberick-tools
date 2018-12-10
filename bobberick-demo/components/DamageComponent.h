#ifndef BOBBERICK_TOOLS_DAMAGECOMPONENT_H
#define BOBBERICK_TOOLS_DAMAGECOMPONENT_H
#include "../../bobberick-framework/src/entity/Component.h"

class DamageComponent : public Component
{
public:
	DamageComponent(const double damage) : damage{ damage } {}
	const double damage;
};

#endif //BOBBERICK_TOOLS_DAMAGECOMPONENT