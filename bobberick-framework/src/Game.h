#ifndef BOBBERICK_TOOLS_GAME_H
#define BOBBERICK_TOOLS_GAME_H

#include "SDL.h"
#include "StateMachine.h"
#include "services/ServiceManager.h"
#include "entity/systems/DrawSystem.h"
#include "entity/systems/InputSystem.h"
#include "util/SDL_Deleter.h"
#include "services/FrameHandler.h"

class Game
{
public:
	virtual ~Game() = default;
	Game();
    bool init(const char* title, int xPos, int yPos, int height, int width, int flags);
    virtual bool setup();
    virtual void start();
    virtual void clean();
    virtual void update();

    bool running() const;

    int getGameWidth() const;
    int getGameHeight() const;

protected:
    SDL_WindowPointer window;
    SDL_RendererPointer renderer;

    int gameHeight;
    int gameWidth;

    bool isRunning;
    //TODO Make a interface for system registring. Maybe in the statemachine?
};


#endif //BOBBERICK_TOOLS_GAME_H
