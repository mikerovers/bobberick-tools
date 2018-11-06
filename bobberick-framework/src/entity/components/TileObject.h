#ifndef BOBBERICK_TOOLS_TILEOBJECT_H
#define BOBBERICK_TOOLS_TILEOBJECT_H

#include <string>
#include "../../util/Vector2D.h"

class TileObject
{
public:
    TileObject(Vector2D* position, const std::string name);
    Vector2D* position;
    const std::string name;
};


#endif //BOBBERICK_TOOLS_TILEOBJECT_H
