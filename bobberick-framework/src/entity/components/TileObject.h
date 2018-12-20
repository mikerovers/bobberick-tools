#ifndef BOBBERICK_TOOLS_TILEOBJECT_H
#define BOBBERICK_TOOLS_TILEOBJECT_H

#include <string>
#include "../../util/Vector2D.h"
#include <SDL.h>
#include "tmxlite/Types.hpp"

class TileObject
{
public:
    TileObject(Vector2D* position, const std::string name, tmx::FloatRect aabb);
    ~TileObject();
    Vector2D* position;
    const std::string name;
	tmx::FloatRect aabb;
};


#endif //BOBBERICK_TOOLS_TILEOBJECT_H
