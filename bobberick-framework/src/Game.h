#ifndef BOBBERICK_TOOLS_GAME_H
#define BOBBERICK_TOOLS_GAME_H

#include "SDL.h"
#include "StateMachine.h"
#include "services/ServiceManager.h"
#include "entity/systems/DrawSystem.h"
#include "entity/systems/InputSystem.h"
#include "util/SDL_Deleter.h"
#include "util/FrameHandler.h"

class Game
{
public:
    Game();
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
    SDL_WindowPointer window;
    SDL_RendererPointer renderer;

    int gameHeight;
    int gameWidth;

    bool isRunning;

    std::shared_ptr<StateMachine> stateMachine;
    std::shared_ptr<FrameHandler> frameHandler;
    //TODO Make a interface for system registring. Maybe in the statemachine?
};


#endif //BOBBERICK_TOOLS_GAME_H
