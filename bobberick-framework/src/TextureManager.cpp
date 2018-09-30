

#include "TextureManager.h"

void TextureManager::clearTexture(std::string id)
{
    //TODO Does this work with RAII object?
    textures.erase(id);
}

bool TextureManager::load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer)
{
    SDL_SurfacePointer pTempSurface = SDL_SurfacePointer(IMG_Load(fileName));

    if (pTempSurface == nullptr) {
        return false;
    }

    SDL_TexturePointer pTexture = SDL_TexturePointer(SDL_CreateTextureFromSurface(renderer.get(), pTempSurface.get()));

    //TODO Does this now clean up?
//    pTempSurface = nullptr;

    if (pTexture != nullptr) {
        textures[id] = pTexture;

        return true;
    }

    return false;
}

void TextureManager::draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer)
{
    SDL_RenderCopyEx(renderer.get(), textures[id].get(), sourceRect, destinationRect, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::init()
{

}
