#include "SettingsService.h"


void SettingsService::init()
{

}

void SettingsService::clean()
{

}

const char* SettingsService::getHumanReadableScancode(SDL_Scancode scancode)
{
	const auto key = SDL_GetScancodeName(scancode);
	return key;
}
