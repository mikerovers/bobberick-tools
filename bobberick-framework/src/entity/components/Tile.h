#ifndef BOBBERICK_TOOLS_TILECOMPONENT_H
#define BOBBERICK_TOOLS_TILECOMPONENT_H

#include <SDL_render.h>
#include <string>
#include "../Component.h"

class Tile
{
public:
    explicit Tile(std::string, int x, int y, int tx, int ty, int width, int height);
    ~Tile();

    std::string sheet;
    int x;
    int y;
    int tx;
    int ty;
    int width;
    int height;

    SDL_Rect getSourceRect();
    SDL_Rect getDestinationRect();
};


#endif //BOBBERICK_TOOLS_TILECOMPONENT_H
