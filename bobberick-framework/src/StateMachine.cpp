#include "StateMachine.h"
#include "services/ServiceManager.h"

void StateMachine::pushState(GameState* pState)
{
	// Make previous state inactive.
	auto& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	if (peekState() != nullptr)
	{
		entityManager.activateEntitiesFromGroup(peekState()->getStateID(), false);
	}

	gameStates.push_back(pState);
	peekState()->onEnter();
}

void StateMachine::popState()
{
	if (!gameStates.empty())
	{
		if (gameStates.back()->onExit())
		{
			auto name = gameStates.back()->getStateID();
			auto& entityManager = ServiceManager::Instance()->getService<EntityManager>();
			std::vector<Entity*> entities = entityManager.getEntitiesFromGroup(name);
			std::for_each(entities.begin(), entities.end(), [](Entity* entity)
			{
				entity->destroy();
			});

			gameStates.back()->setExiting(true);
			gameStates.pop_back();

			// Make previous state active.
			if (peekState() != nullptr)
			{
				entityManager.activateEntitiesFromGroup(peekState()->getStateID(), true);
			}
		}
	}
}

void StateMachine::changeState(GameState* pState)
{
	if (!gameStates.empty())
	{
		auto f = gameStates.size();
        for(auto state : gameStates) {
            popState();
        }
	}

	gameStates.push_back(pState);

	gameStates.back()->onEnter();
}

void StateMachine::update()
{
	if (!gameStates.empty())
	{
		gameStates.back()->update();
		if (gameStates.back()->shouldExit())
		{
			SDL_Log("Popping state.");
			popState();
			if (!gameStates.empty())
			{
				gameStates.back();
			}
		}
	}
}

GameState* StateMachine::peekState()
{
	if (!gameStates.empty())
	{
		return gameStates.back();
	}

	return nullptr;
}

bool StateMachine::isEmpty() const
{
	return gameStates.empty();
}

void StateMachine::init()
{
}

void StateMachine::clean()
{
}
