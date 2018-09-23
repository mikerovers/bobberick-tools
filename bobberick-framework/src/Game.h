#ifndef BOBBERICK_TOOLS_GAME_H
#define BOBBERICK_TOOLS_GAME_H

#include "SDL.h"
#include "StateMachine.h"
#include "services/ServiceManager.h"
#include "entity/systems/DrawSystem.h"

class Game
{
public:
    bool init(const char* title, int xPos, int yPos, int height, int width, int flags);
    void render();
    void handleEvents();
    void clean();
    void update();

    bool running();

    std::shared_ptr<StateMachine> getStateMachine();

    int getGameWidth() const;
    int getGameHeight() const;

private:
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;

    int gameHeight;
    int gameWidth;

    bool isRunning;

    std::shared_ptr<StateMachine> stateMachine;
    //TODO Make a interface for system registring. Maybe in the statemachine?
    std::shared_ptr<DrawSystem> drawSystem;
};


#endif //BOBBERICK_TOOLS_GAME_H
