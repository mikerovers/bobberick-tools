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

	int gameWidth;
	int gameHeight;
	bool music = true;
};


#endif //BOBBERICK_TOOLS_SETTINGSSERVICE_H
