#ifndef BOBBERICK_TOOLS_SHOOTCOMPONENT_H
#define BOBBERICK_TOOLS_SHOOTCOMPONENT_H

#include "../Component.h"

class ShootComponent : public Component
{
public:
	bool canShoot();
	void setShootTimer(unsigned int timer);

	unsigned int lastTime = 0;
	unsigned int timerCount;
};


#endif //BOBBERICK_TOOLS_SHOOTCOMPONENT_H
