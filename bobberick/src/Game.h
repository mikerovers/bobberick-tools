#ifndef BOBBERICK_TOOLS_GAME_H
#define BOBBERICK_TOOLS_GAME_H

#include "SDL2/SDL.h"
#include "StateMachine.h"
#include "services/ServiceManager.h"

class Game
{
public:
    bool init(const char* title, int xPos, int yPos, int height, int width, int flags);
    void render();
    void handleEvents();
    void clean();
    void update();

    bool running();

    StateMachine* getStateMachine();
    SDL_Renderer* getRenderer() const;

    int getGameWidth() const;
    int getGameHeight() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int gameHeight;
    int gameWidth;

    bool isRunning;

    StateMachine* stateMachine;
};


#endif //BOBBERICK_TOOLS_GAME_H
