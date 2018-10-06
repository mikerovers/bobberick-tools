#include <iostream>
#include "../bobberick-framework/src/Game.h"

Game *game = nullptr;

int main(int argc, char **argv) {
    game = new Game();

    if (game->init("Bobberick The Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640,
                   static_cast<Uint32>(false))) {

        while (game->running()) {
            game->render();
        }
    } else {
        std::cout << "Game initialization failure - " << SDL_GetError() << " :( \n";
        return 1;
    }

    game->clean();

    return 0;
}