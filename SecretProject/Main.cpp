/*This source code is copyrighted by GB Games (2018-20++)
and may not be redistributed without written permission.*/

#include "SDL.h"
#include "SDL_TTF.h"
#include "Engine.h"
#include "Tdf_Defs.h"
#include <stdio.h>

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() < 0)
	{
		printf("TTF could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	Engine engine;
	CHK_SUCCESS(engine.AddNewPlayer("Player1"));
	CHK_SUCCESS(engine.AddNewPlayer("Player2"));
	CHK_SUCCESS(engine.AddNewPlayer("Player3"));
	/*CHK_SUCCESS(engine.AddNewPlayer("Player4"));
	CHK_SUCCESS(engine.AddNewPlayer("Player5"));
	CHK_SUCCESS(engine.AddNewPlayer("Player6"));*/

	CHK_SUCCESS(engine.Init());

	//Main loop flag 
	bool quit = false;

	//Event handler 
	SDL_Event e;

	while (!quit)
	{
		//Handle events on queue 
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit 
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else
			{
				CHK_SUCCESS(engine.ProcessEvent(&e));				
			}
		}

		// Move on in the Game
		CHK_SUCCESS(engine.MoveOn());

		// Render the graphics
		CHK_SUCCESS(engine.Render());
	}

	engine.Clean();

	//Quit SDL subsystems 
	SDL_Quit();

	return 0;
}