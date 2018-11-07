#ifndef BOBBERICK_TOOLS_PLAYERSHOOTCOMPONENT_H
#define BOBBERICK_TOOLS_PLAYERSHOOTCOMPONENT_H

#include "../Component.h"

class PlayerShootComponent : public Component
{
public:
	bool canShoot();
	void setShootTimer(unsigned int timer);

	unsigned int lastTime = 0;
	unsigned int timerCount;
};


#endif //BOBBERICK_TOOLS_PLAYERSHOOTCOMPONENT_H
