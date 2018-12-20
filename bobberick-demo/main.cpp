#include <iostream>
#include "../bobberick-framework/src/Game.h"
#include "./BobberGame.h"

//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

int main(int argc, char** argv)
{
	BobberGame game;
	game.setup();
	game.start();


	atexit(SDL_Quit);

	//	_CrtDumpMemoryLeaks();
	return 0;
}
