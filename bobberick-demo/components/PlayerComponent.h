#ifndef BOBBERICK_TOOLS_PLAYERCOMPONENT_H
#define BOBBERICK_TOOLS_PLAYERCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"

class PlayerComponent : public Component
{
public:
	int shootingTimeout{250};
};

#endif //BOBBERICK_TOOLS_PLAYERCOMPONENT_H