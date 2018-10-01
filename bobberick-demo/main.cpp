#include <iostream>
#include "../bobberick-framework/src/Game.h"

Game *game = nullptr;

int main(int argc, char **argv) {
    game = new Game();

    if (game->init("Chaptere 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                   static_cast<Uint32>(false))) {

        while (game->running()) {
            game->render();
        }
    } else {
        std::cout << "game init failure - " << SDL_GetError() << " :( \n";
        return 1;
    }

    game->clean();

    return 0;
}