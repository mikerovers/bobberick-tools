#ifndef BOBBERICK_TOOLS_LEVELFACTORY_H
#define BOBBERICK_TOOLS_LEVELFACTORY_H

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include "entity/components/TilesetComponent.h"
#include "util/SDL_Deleter.h"

class LevelFactory
{
public:
    TilesetComponent* Load(std::string path, SDL_RendererPointer renderer);
private:
    void handleTileLayer(const tmx::TileLayer* tileLayer, TilesetComponent* component);
    void handleObjectLayer(const tmx::ObjectGroup* objectGroup, TilesetComponent* component);
};


#endif //BOBBERICK_TOOLS_LEVELFACTORY_H
