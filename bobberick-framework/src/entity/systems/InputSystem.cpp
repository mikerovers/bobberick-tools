#include "InputSystem.h"
#include "../../services/ServiceManager.h"
#include "../../services/InputHandler.h"

InputSystem::InputSystem(EntityManager &entityManager) : System(entityManager)
{
}

void InputSystem::update()
{
	ServiceManager::Instance()->getService<InputHandler>().update();
}