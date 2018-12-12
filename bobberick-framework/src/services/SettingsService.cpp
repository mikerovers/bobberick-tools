#include "SettingsService.h"


void SettingsService::init()
{

}

void SettingsService::clean()
{

}

const char* SettingsService::getHumanReadableScancode(SDL_Scancode scancode)
{
	return SDL_GetScancodeName(scancode);
}
