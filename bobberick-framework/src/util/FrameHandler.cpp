#include "FrameHandler.h"

FrameHandler::FrameHandler(const int target): target(target), delayTime(1000 / target)
{
	startclock = SDL_GetTicks();
}

void FrameHandler::handleFrame()
{
	int frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < delayTime)
	{
		SDL_Delay(static_cast<Uint32>(delayTime - frameTime));
	}
	deltaclock = SDL_GetTicks() - startclock;
	startclock = SDL_GetTicks();

	if (deltaclock != 0) {
		currentFPS = 1000 / deltaclock;
	}
}

void FrameHandler::updateTicks()
{
	frameStart = SDL_GetTicks();
}

void FrameHandler::setTarget(int targetFrames)
{
	target = targetFrames;
	delayTime = 1000 / target;
}

Uint32 FrameHandler::getCurrentFps() const
{
	return currentFPS;
}