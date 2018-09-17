#ifndef BOBBERICK_TOOLS_RENDERSERVICE_H
#define BOBBERICK_TOOLS_RENDERSERVICE_H


#include <SDL_system.h>
#include "Service.h"

class RenderService : public Service
{
public:
    RenderService();

    void init() override;
    bool createRenderer(SDL_Window* window);
    SDL_Renderer* getRenderer();
    SDL_Renderer* renderer;
private:
};


#endif //BOBBERICK_TOOLS_RENDERSERVICE_H
