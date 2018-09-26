

#include "FontManager.h"

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

bool FontManager::load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer)
{
	return false;
}
