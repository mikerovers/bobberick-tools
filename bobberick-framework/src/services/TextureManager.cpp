#include "TextureManager.h"
#include <iostream>

void TextureManager::clearTexture(std::string id)
{
    //TODO Does this work with RAII object?
    textures.erase(id);
}

bool TextureManager::load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer)
{
	if (textures[id]) {
		return true;
	}

    SDL_SurfacePointer pTempSurface = SDL_SurfacePointer(IMG_Load(fileName));

    if (pTempSurface == nullptr) {
        return false;
    }

	return addTextureFromSurface(pTempSurface, id, renderer);
}

bool TextureManager::addTextureFromSurface(SDL_SurfacePointer surface, std::string id, std::shared_ptr<SDL_Renderer> renderer) {
	SDL_TexturePointer pTexture = SDL_TexturePointer(SDL_CreateTextureFromSurface(renderer.get(), surface.get()));
	if (pTexture != nullptr) {
		textures[id] = pTexture;
		return true;
	} else {
		return false;
	}
}

void TextureManager::draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer, bool flip, double nScale)
{
	auto scaledDest = SDL_Rect{};
	int width = destinationRect->w;
	int height = destinationRect->h;
	width *= nScale;
	height *= nScale;
	scaledDest.w = width;
	scaledDest.h = height;
	scaledDest.x = destinationRect->x;
	scaledDest.y = destinationRect->y;
    SDL_RenderCopyEx(renderer.get(), textures[id].get(), sourceRect, &scaledDest, 0, nullptr, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
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