#include "PlayerShootComponent.h"
#include "SDL.h"


bool PlayerShootComponent::canShoot()
{
	unsigned int currentTime = SDL_GetTicks();
	if (currentTime > lastTime + 250) {
		return true;
	}
	return false;
}

void PlayerShootComponent::setShootTimer()
{
	lastTime = SDL_GetTicks();
}
