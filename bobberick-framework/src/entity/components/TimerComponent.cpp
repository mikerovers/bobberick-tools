#include "TimerComponent.h"
#include "SDL.h"
#include "../../services/ServiceManager.h"
#include "../../services/FrameHandler.h"


bool TimerComponent::isTimerFinished()
{
	unsigned int currentTime = ServiceManager::Instance()->getService<FrameHandler>().getStartClock();
	unsigned int fps = ServiceManager::Instance()->getService<FrameHandler>().getCurrentFps();

	if (currentTime > lastTime + timerCount * 60 / (fps > 0 ? fps : 1)) {
		return true;
	}
	return false;
}

void TimerComponent::setTimer(unsigned int timer)
{
	timerCount = timer;
	lastTime = ServiceManager::Instance()->getService<FrameHandler>().getStartClock();
}
