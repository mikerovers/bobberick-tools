#include "TimerComponent.h"
#include "SDL.h"
#include "../../services/ServiceManager.h"
#include "../../services/FrameHandler.h"


bool TimerComponent::isTimerFinished()
{
	unsigned int currentTime = ServiceManager::Instance()->getService<FrameHandler>().getDeltaClock();
	if (currentTime > lastTime + timerCount) {
		return true;
	}
	return false;
}

void TimerComponent::setTimer(unsigned int timer)
{
	timerCount = timer;
	lastTime = ServiceManager::Instance()->getService<FrameHandler>().getDeltaClock();
}
