#ifndef BOBBERICK_TOOLS_FRAMEHANDLER_H
#define BOBBERICK_TOOLS_FRAMEHANDLER_H

#include <iostream>
#include "SDL.h"
#include "Timer.h"

class FrameHandler
{
public:
	explicit FrameHandler(int target);
	void handleFrame();
	void updateTicks();
	void setTarget(int target);
	Uint32 getCurrentFps() const;

private:
	int target;
	int delayTime;
	Uint32 frameStart;

	Uint32 startclock = 0;
	Uint32 deltaclock = 0;
	Uint32 currentFPS = 0;
};


#endif //BOBBERICK_TOOLS_FRAMEHANDLER_H
