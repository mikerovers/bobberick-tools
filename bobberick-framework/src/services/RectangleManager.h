#ifndef BOBBERICK_TOOLS_RECTANGLEMANAGER_H
#define BOBBERICK_TOOLS_RECTANGLEMANAGER_H

#include <string>
#include <SDL.h>
#include "Service.h"
#include "../util/SDL_Deleter.h"
#include <map>

class RectangleManager : public Service
{
public:
    void init() override;
    void clean() override;
    void draw(SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer, int red, int green, int blue, bool filled);
};


#endif //BOBBERICK_TOOLS_RECTANGLEMANAGER_H
