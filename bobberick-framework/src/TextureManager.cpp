

#include "TextureManager.h"

void TextureManager::clearTexture(std::string id)
{
    //TODO Does this work with RAII object?
    textures.erase(id);
}

bool TextureManager::load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer)
{
	if (textures[id] != nullptr) { // this one already exists
		return false;
	}
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

void TextureManager::draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer, bool flip)
{
    SDL_RenderCopyEx(renderer.get(), textures[id].get(), sourceRect, destinationRect, 0, nullptr, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void TextureManager::setOpacity(std::string id, int opacity) {
	if (opacity > 255) {
		opacity = 255;
	}
	else if (opacity < 0) {
		opacity = 0;
	}
	SDL_SetTextureAlphaMod(textures[id].get(), opacity);
}

void TextureManager::init()
{

}

void TextureManager::clean()
{

}

SDL_TexturePointer TextureManager::getTexture(std::string id)
{
    return textures[id];
}

std::map<std::string, SDL_TexturePointer> TextureManager::getTextures()
{
    return textures;
}
