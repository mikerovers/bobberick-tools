#ifndef BOBBERICK_TOOLS_LEVELFACTORY_H
#define BOBBERICK_TOOLS_LEVELFACTORY_H

#include "entity/components/TilesetComponent.h"
#include "util/SDL_Deleter.h"

class LevelFactory
{
public:
    TilesetComponent* Load(std::string path, SDL_RendererPointer renderer);
};


#endif //BOBBERICK_TOOLS_LEVELFACTORY_H
