#include "RectangleManager.h"

void RectangleManager::draw(SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer, int red, int green, int blue, bool filled)
{
	SDL_SetRenderDrawColor(&*renderer, red, green, blue, 255);
	if (filled) {
		SDL_RenderFillRect(&*renderer, destinationRect);
	} else {
		SDL_RenderDrawRect(&*renderer, destinationRect);
	}
}

void RectangleManager::init()
{

}

void RectangleManager::clean()
{

}