#include "FontManager.h"

void FontManager::clearTexture(std::string id)
{
	//TODO Does this work with RAII object?
	textures.erase(id);
}

bool FontManager::load(const char* fileName, std::string id, const char* text, int size, std::shared_ptr<SDL_Renderer> renderer)
{
	TTF_Font* font = TTF_OpenFont(fileName, size);

	if (font == nullptr) {
		return false;
	}

	SDL_SurfacePointer pTempSurface = SDL_SurfacePointer(TTF_RenderText_Blended(font, text, SDL_Color{0,0,0}));

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

void FontManager::draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer)
{
	SDL_RenderCopyEx(renderer.get(), textures[id].get(), sourceRect, destinationRect, 0, nullptr, SDL_FLIP_NONE);
}

void FontManager::setOpacity(std::string id, int opacity) {
	if (opacity > 255) {
		opacity = 255;
	}
	else if (opacity < 0) {
		opacity = 0;
	}
	SDL_SetTextureAlphaMod(textures[id].get(), opacity);
}

void FontManager::init()
{

}

void FontManager::clean()
{

}
