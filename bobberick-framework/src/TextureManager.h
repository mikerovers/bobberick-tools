#ifndef BOBBERICK_TOOLS_TEXTUREMANAGER_H
#define BOBBERICK_TOOLS_TEXTUREMANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "services/Service.h"
#include "util/SDL_Deleter.h"
#include <map>

class TextureManager : public Service
{
public:
    void init() override;
    void clean() override;
    bool load(const char* fileName, std::string id, std::shared_ptr<SDL_Renderer> renderer);
    void draw(std::string id, SDL_Rect* sourceRect, SDL_Rect* destinationRect, std::shared_ptr<SDL_Renderer> renderer);

    void clearTexture(std::string id);
private:
    std::map<std::string, SDL_TexturePointer> textures;
};


#endif //BOBBERICK_TOOLS_TEXTUREMANAGER_H
