#ifndef BOBBERICK_TOOLS_GAMESTATE_H
#define BOBBERICK_TOOLS_GAMESTATE_H


#include <string>
#include "entity/systems/System.h"

class GameState {
public:
    virtual ~GameState();

    virtual void update() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;
    void addSystem(std::shared_ptr<System> system);
protected:
    std::vector<std::shared_ptr<System>> systems;
};


#endif //BOBBERICK_TOOLS_GAMESTATE_H
