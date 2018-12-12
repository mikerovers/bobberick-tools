#ifndef BOBBERICK_TOOLS_SETTINGSSERVICE_H
#define BOBBERICK_TOOLS_SETTINGSSERVICE_H

#include <string>
#include <SDL.h>
#include "Service.h"
#include "../util/SDL_Deleter.h"
#include <map>

class SettingsService : public Service
{
public:
    void init() override;
    void clean() override;

	static const char* getHumanReadableScancode(SDL_Scancode scancode);

	int gameWidth;
	int gameHeight;
	int advertisementCount;
	bool music = true;
	bool fps = false;

	// Movement key-bindings
	SDL_Scancode left1 = SDL_SCANCODE_LEFT;
	SDL_Scancode right1 = SDL_SCANCODE_RIGHT;
	SDL_Scancode up1 = SDL_SCANCODE_UP;
	SDL_Scancode down1 = SDL_SCANCODE_DOWN;
	SDL_Scancode left2 = SDL_SCANCODE_A;
	SDL_Scancode right2 = SDL_SCANCODE_D;
	SDL_Scancode up2 = SDL_SCANCODE_W;
	SDL_Scancode down2 = SDL_SCANCODE_S;

	// FPS key-bindings
	SDL_Scancode fpsSpdUp = SDL_SCANCODE_Z;
	SDL_Scancode fpsSpdDown = SDL_SCANCODE_X;
	SDL_Scancode fpsSpdReset = SDL_SCANCODE_C;
	// SDL_Scancode fpsShow = SDL_SCANCODE_F11;
	// SDL_Scancode fpsHide = SDL_SCANCODE_F12;

	// Equip comparing weapon key-bindings
	SDL_Scancode equipWeapon1 = SDL_SCANCODE_LSHIFT;
	SDL_Scancode equipWeapon2 = SDL_SCANCODE_RSHIFT;

	// Stop game key-bindings
	SDL_Scancode stopGame1 = SDL_SCANCODE_RETURN;
	SDL_Scancode stopGame2 = SDL_SCANCODE_RETURN2;

	// Pause key-bindings
	SDL_Scancode pauseGame1 = SDL_SCANCODE_ESCAPE;
};


#endif //BOBBERICK_TOOLS_SETTINGSSERVICE_H
