#ifndef BOBBERICK_TOOLS_RENDERSERVICE_H
#define BOBBERICK_TOOLS_RENDERSERVICE_H


#include <SDL_system.h>
#include <memory>
#include "Service.h"

class RenderService : public Service
{
public:
    RenderService();

    void init() override;
    bool createRenderer(std::shared_ptr<SDL_Window> window);
    std::shared_ptr<SDL_Renderer> getRenderer();
    std::shared_ptr<SDL_Renderer> renderer;
private:
};


#endif //BOBBERICK_TOOLS_RENDERSERVICE_H
