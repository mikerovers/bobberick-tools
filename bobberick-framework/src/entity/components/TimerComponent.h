#ifndef BOBBERICK_TOOLS_TIMERCOMPONENT_H
#define BOBBERICK_TOOLS_TIMERCOMPONENT_H

#include "../Component.h"

class TimerComponent : public Component
{
public:
	bool isTimerFinished();
	void setTimer(unsigned int timer);

	unsigned int lastTime = 0;
	unsigned int timerCount;
};


#endif //BOBBERICK_TOOLS_TIMERCOMPONENT_H
