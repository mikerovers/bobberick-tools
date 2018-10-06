#ifndef BOBBERICK_TOOLS_RENDERSERVICE_H
#define BOBBERICK_TOOLS_RENDERSERVICE_H


#include <SDL_system.h>
#include <memory>
#include "Service.h"
#include "../util/SDL_Deleter.h"

class RenderService : public Service
{
public:
    RenderService();

    void init() override;
    void clean() override;
    bool createRenderer(std::shared_ptr<SDL_Window> window);
    SDL_RendererPointer getRenderer();
    SDL_RendererPointer renderer;
private:
};


#endif //BOBBERICK_TOOLS_RENDERSERVICE_H
