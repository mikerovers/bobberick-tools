#include <iostream>
#include "../bobberick-framework/src/Game.h"
#include "./BobberGame.h"

std::unique_ptr<Game> game = nullptr;

int main(int argc, char **argv) {
    game = std::unique_ptr<Game>(new BobberGame());
    game->setup();
    game->start();

    return 0;
}