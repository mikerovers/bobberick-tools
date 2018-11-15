#include "TimerComponent.h"
#include "SDL.h"


bool TimerComponent::isTimerFinished()
{
	unsigned int currentTime = SDL_GetTicks();
	if (currentTime > lastTime + timerCount) {
		return true;
	}
	return false;
}

void TimerComponent::setTimer(unsigned int timer)
{
	timerCount = timer;
	lastTime = SDL_GetTicks();
}
