// ColourCode.cpp : Defines the entry point for the console application.
// This code is taken from an example given to us by gareth when working with SDL2 pong

#include "stdafx.h"
#include "SDL.h"
#include "Game.h"


int main(int argc, char* argv[])
{
	// initialise the game
	game.init("SDL Serial", 100, 100, 640, 480, 0);

	// create a game loop
	while (game.running()) {

		// choose a framerate - in this case we are using 1000%40 which means 
		// 25 frames per second (quite slow)
		int increment = SDL_GetTicks() % 25;

		// if modulo returns 0 trigger one frame in our game
		if (increment == 0) {

			game.handleEvents();
			game.update();
			game.render();

		}
	}

	// when the game ends clean SDL and Serial
	game.clean();

    return 0;
}

