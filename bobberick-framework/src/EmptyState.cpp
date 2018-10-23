#include "EmptyState.h"

std::string EmptyState::getStateID() const
{
    return "empty";
}

bool EmptyState::shouldExit()
{
    return false;
}

bool EmptyState::onExit()
{
    std::cout << "Empty state exited.";

    return true;
}

bool EmptyState::onEnter()
{
    std::cout << "Empty state entered.";

    return true;
}

void EmptyState::update()
{

}
