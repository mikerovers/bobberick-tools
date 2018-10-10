#include "RenderService.h"

SDL_RendererPointer RenderService::getRenderer()
{
    return renderer;
}

void RenderService::init()
{
}

bool RenderService::createRenderer(std::shared_ptr<SDL_Window> window)
{
    renderer = SDL_RendererPointer(SDL_CreateRenderer(window.get(), -1, 0));

    return renderer != nullptr;
}

RenderService::RenderService()
{

}

void RenderService::clean()
{

}
