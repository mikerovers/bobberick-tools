#include "KeyMappingSystem.h"

void KeyMappingSystem::update()
{
	if (skipForRepeat > 600) {
		skipForRepeat = 0;
	}
	else {
		skipForRepeat++;
	}

	if (inputHandler.isKeyDown(settings.left1))
	{
		settings.left1 = inputHandler.getKeyDown();
	}
}