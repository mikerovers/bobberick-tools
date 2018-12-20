#ifndef BOBBERICK_TOOLS_TILE_H
#define BOBBERICK_TOOLS_TILE_H

#include <string>
#include <SDL.h>

class Tile
{
public:
    explicit Tile(std::string texture, int x, int y, int tx, int ty, int width, int height);
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


#endif //BOBBERICK_TOOLS_TILE_H
