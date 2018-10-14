#ifndef BOBBERICK_TOOLS_FONTMANAGER_H
#define BOBBERICK_TOOLS_FONTMANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_TTF.h>
#include "TextureManager.h"
#include "util/SDL_Deleter.h"
#include <map>

class FontManager : public Service
{
public:
	void init() override;
	void clean() override;
    bool load(const char* fileName, std::string id, const char* text, int size, std::shared_ptr<SDL_Renderer> renderer);
	void draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer);
	void clearTexture(std::string id);
protected:
	std::map<std::string, SDL_TexturePointer> textures;
};


#endif //BOBBERICK_TOOLS_FONTMANAGER_H
