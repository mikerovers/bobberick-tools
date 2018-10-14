#ifndef BOBBERICK_TOOLS_LEVEL_H
#define BOBBERICK_TOOLS_LEVEL_H

#include <string>
#include "util/SDL_Deleter.h"
#include "tmxlite/Map.hpp"
#include "entity/components/Tile.h"
#include "entity/components/TileSetComponent.h"

class LevelFactory
{
public:
    TileSetComponent* Load(std::string path, SDL_RendererPointer renderer);
};


#endif //BOBBERICK_TOOLS_LEVEL_H
