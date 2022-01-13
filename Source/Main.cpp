#include "MainRenderWindow.h"

int main()
{
	//Functions for checking memory leaks.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Main game window instance.
	Pong::MainRenderWindow mainWindow;

	//If text font resource is not present in resources the game won't run and quits.
	if (!mainWindow.Initialize())
	{
		return EXIT_FAILURE;
	}

	//Main Game Loop.
	mainWindow.RunMainGameLoop();

	//Program End.
	return EXIT_SUCCESS;
}