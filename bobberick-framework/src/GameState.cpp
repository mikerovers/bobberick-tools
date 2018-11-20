#include "GameState.h"

GameState::~GameState()
{

}

void GameState::addSystem(std::shared_ptr<System> system)
{
    systems.push_back(system);
}

void GameState::setExiting(const bool isExiting)
{
    exiting = isExiting;
}
