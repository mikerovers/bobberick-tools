#ifndef BOBBERICK_TOOLS_TILESETCOMPONENT_H
#define BOBBERICK_TOOLS_TILESETCOMPONENT_H

#include <map>
#include <vector>
#include "../../util/SDL_Deleter.h"
#include "Tile.h"

typedef int gid;

class TileSetComponent : public Component
{
public:
    int rows;
    int cols;
    int tileWidth;
    int tileHeight;
    std::map<gid, std::string> tileSets;
    std::vector<Tile*> tiles;
};


#endif //BOBBERICK_TOOLS_TILESETCOMPONENT_H
