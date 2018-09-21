#include <iostream>
#include "../bobberick-framework/src/Game.h"

Game* game = nullptr;
const int FPS = 60;
float DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
    Uint32 frameStart, frameTime;

    game = new Game();

    if (game->init("Chaptere 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, static_cast<Uint32>(false))) {

        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME) {
                SDL_Delay(static_cast<Uint32>((int) (DELAY_TIME - frameTime)));
            }
        }
    } else {
        std::cout << "game init failure - " << SDL_GetError() << " :( \n";
        return 1;
    }

    game->clean();

    return 0;
}