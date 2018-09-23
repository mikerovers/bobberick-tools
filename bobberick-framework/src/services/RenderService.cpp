#include "RenderService.h"

std::shared_ptr<SDL_Renderer> RenderService::getRenderer()
{
    return renderer;
}

void RenderService::init()
{
}

bool RenderService::createRenderer(std::shared_ptr<SDL_Window> window)
{
    renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(), -1, 0), SDL_DestroyRenderer);

    return renderer != nullptr;
}

RenderService::RenderService()
{

}
