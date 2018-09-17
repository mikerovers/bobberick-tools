#include <iostream>
#include <SDL2/SDL.h>
#include "../bobberick-framework/src/Game.h"

Game* game = 0;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main()
{
    Uint32 frameStart, frameTime;

    game = new Game();

    if (game->init("Chaptere 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, static_cast<Uint32>(false))) {

        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME) {
                SDL_Delay((int) (DELAY_TIME - frameTime));
            }
        }
    } else {
        std::cout << "game init failure - " << SDL_GetError() << " :( \n";

        return 1;
    }

    game->clean();

    return 0;
}