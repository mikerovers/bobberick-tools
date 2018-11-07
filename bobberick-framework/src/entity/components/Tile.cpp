#include "Tile.h"

Tile::Tile(std::string texture, int x, int y, int tx, int ty, int width, int height)
    : x(x), y(y), tx(tx), ty(ty), width(width), height(height)
{
    sheet = texture;
}

SDL_Rect Tile::getSourceRect()
{
    SDL_Rect srcRect;
    srcRect.x = tx;
    srcRect.y = ty;
    srcRect.w = width;
    srcRect.h = height;

    return srcRect;
}

SDL_Rect Tile::getDestinationRect()
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    return destRect;
}




