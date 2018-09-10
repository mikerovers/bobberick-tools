#include "RenderService.h"

SDL_Renderer *RenderService::getRenderer()
{
    return renderer;
}

void RenderService::init()
{
}

bool RenderService::createRenderer(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, 0);

    return renderer != nullptr;
}

RenderService::RenderService()
{

}
