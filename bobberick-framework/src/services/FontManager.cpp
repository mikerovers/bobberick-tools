#include "FontManager.h"
#include "ServiceManager.h"
#include <iostream>

void FontManager::clearFont(std::string fontId)
{
	//TODO Does this work with RAII object?
	fonts.erase(fontId);
}

bool FontManager::loadFont(const char* fileName, const std::string fontId, const int size)
{
	TTF_Font* font = TTF_OpenFont(fileName, size);

	if (font == nullptr) {
		return false;
	} else {
		if (fonts[fontId] != nullptr) {
			fonts.erase(fontId);
		}
		fonts[fontId] = font;
		return true;
	}
}

bool FontManager::createText(std::string fontId, std::string textureId, std::string text, SDL_RendererPointer renderer) {
	SDL_Color color { 0, 0, 0 };
	if (fonts[fontId] != nullptr) {
		SDL_SurfacePointer pTempSurface = SDL_SurfacePointer(TTF_RenderText_Blended(fonts[fontId], text.c_str(), color));
		if (pTempSurface != nullptr) {
			return ServiceManager::Instance()->getService<TextureManager>().addTextureFromSurface(pTempSurface, textureId, renderer);
		} else {
			return false;
		}
	} else {
		return false;
	}
}

// For now, I'll use this space to load in all font-size combinations we need. But you can also use loadFont() from outside, of course.
void FontManager::init()
{
	if (!loadFont("assets/font/mono.ttf", "monoMedium", 30)) {
		std::cout << SDL_GetError();
	}
	if (!loadFont("assets/font/mono.ttf", "monoSmall", 15)) {
		std::cout << SDL_GetError();
	}
	if (!loadFont("assets/font/font.ttf", "defaultMedium", 30)) {
		std::cout << SDL_GetError();
	}
	if (!loadFont("assets/font/font.ttf", "defaultLarge", 56)) {
		std::cout << SDL_GetError();
	}
}

void FontManager::clean()
{

}
