#include "ShootComponent.h"
#include "SDL.h"


bool ShootComponent::canShoot()
{
	unsigned int currentTime = SDL_GetTicks();
	if (currentTime > lastTime + timerCount) {
		return true;
	}
	return false;
}

void ShootComponent::setShootTimer(unsigned int timer)
{
	timerCount = timer;
	lastTime = SDL_GetTicks();
}
