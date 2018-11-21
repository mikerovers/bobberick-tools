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

void TextureManager::preloadTextures(std::shared_ptr<SDL_Renderer> renderer) 
{
	// misc
	load("assets/teamcpp_logo.bmp", "logo", renderer);
	load("assets/image/collision.png", "collisionBox", renderer);

	// button
	load("assets/image/button/exitbutton.png", "exitButton", renderer);
	load("assets/image/button/helpbutton.png", "helpButton", renderer);
	load("assets/image/button/optionsbutton.png", "optionsButton", renderer);
	load("assets/image/button/startgamebutton.png", "startGameButton", renderer);

	// character
	load("assets/image/character/character.png", "character", renderer);
	load("assets/image/character/character_casting.png", "characterCasting", renderer);
	load("assets/image/character/character_shield.png", "characterShield", renderer);
	load("assets/image/character/character_shooting.png", "characterShooting", renderer);

	// enemies
	load("assets/image/Enemies/birds1.png", "birds", renderer);
	load("assets/image/Enemies/chicken_brown.png", "chickenBrown", renderer);
	load("assets/image/Enemies/chicken_white.png.png", "chickenWhite", renderer);
	load("assets/image/Enemies/end_boss.png", "endBoss", renderer);
	load("assets/image/Enemies/factory.png", "factory", renderer);
	load("assets/image/Enemies/fire_wizard.png", "fireWizard", renderer);
	load("assets/image/Enemies/fire_wizard_casting.png", "fireWizardCasting", renderer);
	load("assets/image/Enemies/house.png", "house", renderer);
	load("assets/image/Enemies/magic_circle.png", "magicCircle", renderer);
	load("assets/image/Enemies/orc_piratess.png", "orc", renderer);
	load("assets/image/Enemies/zombie.png", "zombie", renderer);

	// gui
	load("assets/image/gui/hud_gold.png", "hudGold", renderer);
	load("assets/image/gui/hud_xp.png", "hudXp", renderer);
	load("assets/image/gui/playbutton.bmp", "playButton", renderer);

	// items
	load("assets/image/items/potion.png", "potion", renderer);

	// projectiles
	load("assets/image/projectiles/bolt.png", "bolt", renderer);
	load("assets/image/projectiles/bullet_ball_grey.png", "bullet", renderer);
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