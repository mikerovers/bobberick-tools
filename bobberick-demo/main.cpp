#include <iostream>
#include "../bobberick-framework/src/Game.h"
#include "./BobberGame.h"

//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

std::unique_ptr<Game> game = nullptr;

int main(int argc, char** argv)
{
	game = std::unique_ptr<Game>(new BobberGame());
	game->setup();
	game->start();


	atexit(SDL_Quit);

//	_CrtDumpMemoryLeaks();
	return 0;
}
