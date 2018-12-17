#ifndef BOBBERICK_TOOLS_BUTTONCOMPONENT_H
#define BOBBERICK_TOOLS_BUTTONCOMPONENT_H

#include <functional>
#include "../Component.h"

enum button_state
{
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
};

class ButtonComponent : public Component
{
public:
    explicit ButtonComponent(std::function<void()> callback);
    void setCallback(std::function<void()> cb);
    void runCallback();
    bool getReleased() const;
    void setReleased(const bool cl);
	bool getPressed() const;
	void setPressed(const bool cl);
private:
    std::function<void()> callback;
    bool released;
	bool pressed;
};


#endif //BOBBERICK_TOOLS_BUTTONCOMPONENT_H
