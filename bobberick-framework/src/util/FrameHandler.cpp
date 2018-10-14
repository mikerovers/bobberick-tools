#include "FrameHandler.h"

FrameHandler::FrameHandler(const int target): target(target), delayTime(1000 / target)
{
	countedFrames = 0;
	fpsTimer.start();
}

void FrameHandler::handleFrame()
{
    int frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < delayTime) {
        SDL_Delay(static_cast<Uint32>(delayTime - frameTime));
    }
}

void FrameHandler::updateTicks()
{
    frameStart = SDL_GetTicks();
	//Calculate and correct fps 
	avgFps = countedFrames / ( fpsTimer.getTicks() / 1000.f ); 
	countedFrames++;
}

void FrameHandler::setTarget(int targetFrames)
{
    target = targetFrames;
    delayTime = 1000 / target;
}

float FrameHandler::getAvgFps() const
{
	return avgFps;
}
