#include "TimerComponent.h"
#include "SDL.h"
#include "../../services/ServiceManager.h"
#include "../../services/FrameHandler.h"


bool TimerComponent::isTimerFinished() const
{
	const unsigned int currentTime = ServiceManager::Instance()->getService<FrameHandler>().getStartClock();
	const unsigned int fps = ServiceManager::Instance()->getService<FrameHandler>().getCurrentFps();

	return currentTime > lastTime + timerCount * 60 / (fps > 0 ? fps : 1);
}

void TimerComponent::setTimer(unsigned int timer)
{
	timerCount = timer;
	lastTime = ServiceManager::Instance()->getService<FrameHandler>().getStartClock();
}
