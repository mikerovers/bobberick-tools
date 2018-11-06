#include "PlayerShootComponent.h"
#include "SDL.h"


bool PlayerShootComponent::canShoot()
{
	unsigned int currentTime = SDL_GetTicks();
	if (currentTime > lastTime + timerCount) {
		return true;
	}
	return false;
}

void PlayerShootComponent::setShootTimer(unsigned int timer)
{
	timerCount = timer;
	lastTime = SDL_GetTicks();
}
