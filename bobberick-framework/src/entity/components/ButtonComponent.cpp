#include <utility>

#include "ButtonComponent.h"

ButtonComponent::ButtonComponent(std::function<void()> callback): callback(std::move(callback)), released(true)
{

}

void ButtonComponent::setCallback(std::function<void()> cb)
{
    callback = cb;
}

bool ButtonComponent::getReleased() const
{
    return released;
}

void ButtonComponent::setReleased(const bool cl)
{
    released = cl;
}

void ButtonComponent::runCallback()
{
    callback();
}
