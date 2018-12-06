#ifndef BOBBERICK_TOOLS_GAMESTATE_H
#define BOBBERICK_TOOLS_GAMESTATE_H

#include <string>
#include "entity/systems/System.h"
#include <vector>

class GameState {
public:
    virtual ~GameState() = default;

    virtual void update() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

	virtual bool shouldExit() = 0; // Some states may know themselves when they're done. They need to be able to tell the state machine to pop them off.
    virtual std::string getStateID() const = 0;
    void addSystem(std::unique_ptr<System> system);
    void setExiting(bool isExiting);
protected:
    std::vector<std::unique_ptr<System>> systems;
    bool exiting = false;
};


#endif //BOBBERICK_TOOLS_GAMESTATE_H
