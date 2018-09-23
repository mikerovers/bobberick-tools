

#include "TextureManager.h"

void TextureManager::clearTexture(std::string id)
{
    textures.erase(id);
}

bool TextureManager::load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName);

    if (pTempSurface == nullptr) {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer.get(), pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != nullptr) {
        textures[id] = pTexture;

        return true;
    }

    return false;
}

void TextureManager::draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer)
{
    SDL_RenderCopyEx(renderer.get(), textures[id], sourceRect, destinationRect, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::init()
{

}
