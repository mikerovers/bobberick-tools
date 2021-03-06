#ifndef BOBBERICK_TOOLS_TILESETCOMPONENT_H
#define BOBBERICK_TOOLS_TILESETCOMPONENT_H

#include "../Component.h"
#include "Tile.h"
#include "TileObject.h"
#include <map>
#include <vector>

typedef int gid;

class TilesetComponent : public Component
{
public:
    std::string sheet;
    int rows;
    int cols;
    int tileWidth;
    int tileHeight;
    std::map<gid, std::string> tileSets;
    std::vector<Tile*> tiles;
    std::vector<TileObject*> objects;
};


#endif //BOBBERICK_TOOLS_TILESETCOMPONENT_H
