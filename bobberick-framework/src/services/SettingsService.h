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

	bool isKeyTaken(SDL_Scancode key);

	static const char* getHumanReadableScancode(SDL_Scancode scancode);

	int gameWidth;
	int gameHeight;
	int advertisementCount;
	bool music = true;
	bool fps = false;

	SDL_Scancode keyToChange;

	// Movement key-bindings
	SDL_Scancode left1;
	SDL_Scancode right1;
	SDL_Scancode up1;
	SDL_Scancode down1;
	SDL_Scancode left2;
	SDL_Scancode right2;
	SDL_Scancode up2;
	SDL_Scancode down2;

	// Shield and shooting key-bindings
	// SDL_Scancode shootNormal = ; // TODO: Add shooting to the key binding
	// SDL_Scancode shootMagic = ; // TODO: Add shooting to the key binding
	SDL_Scancode activateShield = SDL_SCANCODE_SPACE;

	// FPS key-bindings
	SDL_Scancode fpsSpdDown;
	SDL_Scancode fpsSpdUp;
	SDL_Scancode fpsSpdReset;
	SDL_Scancode fpsShow;
	SDL_Scancode fpsHide;

	// Equip comparing weapon key-bindings
	SDL_Scancode equipWeapon1;
	SDL_Scancode equipWeapon2;

	// Stop game key-bindings
	SDL_Scancode stopGame1;
	SDL_Scancode stopGame2;

	// Pause key-bindings
	SDL_Scancode pauseGame1;
};


#endif //BOBBERICK_TOOLS_SETTINGSSERVICE_H
