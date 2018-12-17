#include "SettingsService.h"
#include "ServiceManager.h"
#include "SaveService.h"

void SettingsService::init()
{
	auto& save = ServiceManager::Instance()->getService<SaveService>();
	save.load();

	// Movement keys
	if (save.has("left1"))
		left1 = save.get<SDL_Scancode>("left1");
	else
		left1 = SDL_SCANCODE_LEFT;
	if (save.has("right1"))
		right1 = save.get<SDL_Scancode>("right1");
	else
		right1 = SDL_SCANCODE_RIGHT;
	if (save.has("up1"))
		up1 = save.get<SDL_Scancode>("up1");
	else
		up1 = SDL_SCANCODE_UP;
	if (save.has("down1"))
		down1 = save.get<SDL_Scancode>("down1");
	else
		down1 = SDL_SCANCODE_DOWN;
	if (save.has("left2"))
		left2 = save.get<SDL_Scancode>("left2");
	else
		left2 = SDL_SCANCODE_A;
	if (save.has("right2"))
		right2 = save.get<SDL_Scancode>("right2");
	else
		right2 = SDL_SCANCODE_D;
	if (save.has("up2"))
		up2 = save.get<SDL_Scancode>("up2");
	else
		up2 = SDL_SCANCODE_W;
	if (save.has("down2"))
		down2 = save.get<SDL_Scancode>("down2");
	else
		down2 = SDL_SCANCODE_S;

	// FPS keys
	if (save.has("fpsSpdUp"))
		fpsSpdUp = save.get<SDL_Scancode>("fpsSpdUp");
	else
		fpsSpdUp = SDL_SCANCODE_X;
	if (save.has("fpsSpdDown"))
		fpsSpdDown = save.get<SDL_Scancode>("fpsSpdDown");
	else
		fpsSpdDown = SDL_SCANCODE_Z;
	if (save.has("fpsSpdReset"))
		fpsSpdReset = save.get<SDL_Scancode>("fpsSpdReset");
	else
		fpsSpdReset = SDL_SCANCODE_C;
	if (save.has("fpsShow"))
		fpsShow = save.get<SDL_Scancode>("fpsShow");
	else
		fpsShow = SDL_SCANCODE_F12;
	if (save.has("fpsHide"))
		fpsHide = save.get<SDL_Scancode>("fpsHide");
	else
		fpsHide = SDL_SCANCODE_F11;

	// Equip weapon keys
	if (save.has("equipWeapon1"))
		equipWeapon1 = save.get<SDL_Scancode>("equipWeapon1");
	else
		equipWeapon1 = SDL_SCANCODE_LSHIFT;
	if (save.has("equipWeapon2"))
		equipWeapon2 = save.get<SDL_Scancode>("equipWeapon2");
	else
		equipWeapon2 = SDL_SCANCODE_RSHIFT;

	// Stop game keys
	if (save.has("stopGame1"))
		stopGame1 = save.get<SDL_Scancode>("stopGame1");
	else
		stopGame1 = SDL_SCANCODE_RETURN;
	if (save.has("stopGame2"))
		stopGame2 = save.get<SDL_Scancode>("stopGame2");
	else
		stopGame2 = SDL_SCANCODE_RETURN2;

	// Pause game keys
	if (save.has("pauseGame1"))
		pauseGame1 = save.get<SDL_Scancode>("pauseGame1");
	else
		pauseGame1 = SDL_SCANCODE_ESCAPE;
}

void SettingsService::clean()
{

}

const char* SettingsService::getHumanReadableScancode(SDL_Scancode scancode)
{
	return SDL_GetScancodeName(scancode);
}

bool SettingsService::isKeyTaken(SDL_Scancode key)
{
	// auto& settings = ServiceManager::Instance()->getService<SettingsService>();
	// return key == settings.left1 || key == settings.right1 || key == settings.up1 || key == settings.down1 ||
	// 	key == settings.left2 || key == settings.right2 || key == settings.up2 || key == settings.down2 ||
	// 	key == settings.fpsSpdUp || key == settings.fpsSpdDown || key == settings.fpsSpdReset ||
	// 	key == settings.fpsShow || key == settings.fpsHide || key == settings.equipWeapon1 || key == settings.equipWeapon2 ||
	// 	key == settings.stopGame1 || key == settings.stopGame2 || key == settings.pauseGame1 || key == settings.activateShield;
	return key == left1 || key == right1 || key == up1 || key == down1 ||
		key == left2 || key == right2 || key == up2 || key == down2 ||
		key == fpsSpdUp || key == fpsSpdDown || key == fpsSpdReset ||
		key == fpsShow || key == fpsHide || key == equipWeapon1 || key == equipWeapon2 ||
		key == stopGame1 || key == stopGame2 || key == pauseGame1 || key == activateShield;
}
