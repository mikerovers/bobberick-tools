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
    bool loadFont(const char* fileName, std::string fontId, const int size);
	bool createText(std::string fontId, std::string textureId, std::string text, std::shared_ptr<SDL_Renderer> renderer);
	void clearFont(std::string fontId);
protected:
	std::map<std::string, TTF_Font*> fonts;
};


#endif //BOBBERICK_TOOLS_FONTMANAGER_H
