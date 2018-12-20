#include "GameState.h"

void GameState::setExiting(const bool isExiting)
{
    exiting = isExiting;
}

void GameState::addSystem(std::unique_ptr<System> system)
{
    systems.push_back(std::unique_ptr<System>(std::move(system)));
}
