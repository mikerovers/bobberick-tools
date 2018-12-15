#include <utility>

#include "ButtonComponent.h"

ButtonComponent::ButtonComponent(std::function<void()> callback): callback(std::move(callback)), released(false), pressed(false)
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

bool ButtonComponent::getPressed() const
{
	return pressed;
}

void ButtonComponent::setPressed(const bool cl)
{
	pressed = cl;
}

void ButtonComponent::runCallback()
{
    callback();
}
