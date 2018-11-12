#include "TestState.h"

std::string TestState::getStateID() const
{
    return "TestState";
}

bool TestState::shouldExit()
{
    return false;
}

bool TestState::onEnter()
{
    std::cout << "Entered TestState" << std::endl;

    return true;
}

void TestState::update()
{

}

bool TestState::onExit()
{
    return false;
}
