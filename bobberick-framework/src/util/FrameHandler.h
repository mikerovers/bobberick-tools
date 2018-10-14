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
	float getAvgFps() const;

private:
	int target;
	int delayTime;
	Uint32 frameStart;
	int countedFrames;
	Timer fpsTimer;
	float avgFps;
};


#endif //BOBBERICK_TOOLS_FRAMEHANDLER_H
