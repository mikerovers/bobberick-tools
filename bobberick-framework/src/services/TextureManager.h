#ifndef BOBBERICK_TOOLS_TEXTUREMANAGER_H
#define BOBBERICK_TOOLS_TEXTUREMANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Service.h"
#include "../util/SDL_Deleter.h"
#include <map>

class TextureManager : public Service
{
public:
    void init() override;
    void clean() override;
    bool load(const char *fileName, std::string id, SDL_RendererPointer renderer);
	// FontManager's SDL_TTF must create a surface from text, but TextureManager is responsible for creating textures (from surfaces), which is the only reason this method is neccessary.
	bool addTextureFromSurface(SDL_SurfacePointer surface, std::string id, SDL_RendererPointer renderer);
    void draw(std::string id, SDL_Rect *sourceRect, SDL_Rect *destinationRect, SDL_RendererPointer renderer, bool flip,
			  double nScale = 1);

	void setOpacity(std::string id, int opacity);
	SDL_TexturePointer getTexture(std::string id);
	std::map<std::string, SDL_TexturePointer> getTextures();

    void clearTexture(std::string id);
private:
    std::map<std::string, SDL_TexturePointer> textures;
};


#endif //BOBBERICK_TOOLS_TEXTUREMANAGER_H
