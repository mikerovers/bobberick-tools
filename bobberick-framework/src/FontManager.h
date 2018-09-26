#ifndef BOBBERICK_TOOLS_FONTMANAGER_H
#define BOBBERICK_TOOLS_FONTMANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_TTF.h>
#include "TextureManager.h"
#include "util/SDL_Deleter.h"
#include <map>

class FontManager : public TextureManager
{
public:
    bool load(const char* fileName, std::string id, const char* text, int size, std::shared_ptr<SDL_Renderer> renderer);
	bool load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer) override;
};


#endif //BOBBERICK_TOOLS_FONTMANAGER_H
