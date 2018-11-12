#include "TileObject.h"

TileObject::TileObject(Vector2D *position, const std::string name) : position(position), name(name)
{

}

TileObject::~TileObject()
{
    delete position;
}
