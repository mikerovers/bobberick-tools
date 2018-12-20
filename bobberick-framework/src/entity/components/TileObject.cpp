#include "TileObject.h"
#include <SDL.h>

TileObject::TileObject(Vector2D *position, const std::string name, const tmx::FloatRect aabb) : position(position), name(name), aabb(aabb)
{
}

TileObject::~TileObject()
{
    delete position;
}
