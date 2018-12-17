#include "KeyMappingSystem.h"

KeyMappingSystem::KeyMappingSystem(EntityManager& entityManager) : System(entityManager)
{
}


void KeyMappingSystem::update()
{
	if (inputHandler.isMappingKey())
	{
		if (settings.keyToChange == settings.left1)
		{
			if (settings.keyToChange != settings.left1)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.left1 = inputHandler.newKey;
				save.keep("left1", settings.left1);
			}
		}

		if (settings.keyToChange == settings.right1)
		{
			if (settings.keyToChange != settings.right1)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.right1 = inputHandler.newKey;
				save.keep("right1", settings.right1);
			}
		}

		if (settings.keyToChange == settings.up1)
		{
			if (settings.keyToChange != settings.up1)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.up1 = inputHandler.newKey;
				save.keep("up1", settings.up1);
			}
		}

		if (settings.keyToChange == settings.down1)
		{
			if (settings.keyToChange != settings.down1)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.down1 = inputHandler.newKey;
				save.keep("down1", settings.down1);
			}
		}

		if (settings.keyToChange == settings.left2)
		{
			if (settings.keyToChange != settings.left2)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.left2 = inputHandler.newKey;
				save.keep("left2", settings.left2);
			}
		}

		if (settings.keyToChange == settings.right2)
		{
			if (settings.keyToChange != settings.right2)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.right2 = inputHandler.newKey;
				save.keep("right2", settings.right2);
			}
		}

		if (settings.keyToChange == settings.up2)
		{
			if (settings.keyToChange != settings.up2)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.up2 = inputHandler.newKey;
				save.keep("up2", settings.up2);
			}
		}

		if (settings.keyToChange == settings.down2)
		{
			if (settings.keyToChange != settings.down2)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.down2 = inputHandler.newKey;
				save.keep("down2", settings.down2);
			}
		}

		if (settings.keyToChange == settings.fpsSpdUp)
		{
			if (settings.keyToChange != settings.fpsSpdUp)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.fpsSpdUp = inputHandler.newKey;
				save.keep("fpsSpdUp", settings.fpsSpdUp);
			}
		}

		if (settings.keyToChange == settings.fpsSpdDown)
		{
			if (settings.keyToChange != settings.fpsSpdDown)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.fpsSpdDown = inputHandler.newKey;
				save.keep("fpsSpdDown", settings.fpsSpdDown);
			}
		}

		if (settings.keyToChange == settings.fpsSpdReset)
		{
			if (settings.keyToChange != settings.fpsSpdReset)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.fpsSpdReset = inputHandler.newKey;
				save.keep("fpsSpdReset", settings.fpsSpdReset);
			}
		}

		if (settings.keyToChange == settings.fpsShow)
		{
			if (settings.keyToChange != settings.fpsShow)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.fpsShow = inputHandler.newKey;
				save.keep("fpsShow", settings.fpsShow);
			}
		}

		if (settings.keyToChange == settings.fpsHide)
		{
			if (settings.keyToChange != settings.fpsHide)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.fpsHide = inputHandler.newKey;
				save.keep("fpsHide", settings.fpsHide);
			}
		}

		if (settings.keyToChange == settings.equipWeapon1)
		{
			if (settings.keyToChange != settings.equipWeapon1)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.equipWeapon1 = inputHandler.newKey;
				save.keep("equipWeapon1", settings.equipWeapon1);
			}
		}

		if (settings.keyToChange == settings.pauseGame1)
		{
			if (settings.keyToChange != settings.pauseGame1)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.pauseGame1 = inputHandler.newKey;
				save.keep("pauseGame1", settings.pauseGame1);
			}
		}

		if (settings.keyToChange == settings.activateShield)
		{
			if (settings.keyToChange != settings.activateShield)
			{
				inputHandler.isMappingKey(false);
			}
			if (!settings.isKeyTaken(inputHandler.newKey))
			{
				settings.activateShield = inputHandler.newKey;
				save.keep("activateShield", settings.activateShield);
			}
		}
	}
}
