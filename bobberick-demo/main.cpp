#include <iostream>
#include "../bobberick-framework/src/Game.h"

Game *game = nullptr;

int main(int argc, char **argv) {
    const int FPS = 60;
    const int DELAY_TIME = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    if (game->init("Chaptere 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                   static_cast<Uint32>(false))) {

        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME) {
                // todo: move this to game engine
                SDL_Delay(static_cast<Uint32>(DELAY_TIME - frameTime));
            }
        }
    } else {
        std::cout << "game init failure - " << SDL_GetError() << " :( \n";
        return 1;
    }

    game->clean();

    return 0;
}