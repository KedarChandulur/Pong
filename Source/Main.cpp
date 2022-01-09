#include "MainRenderWindow.h"

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Pong::MainRenderWindow mainWindow;

	if (!mainWindow.Initialize())
	{
		return EXIT_FAILURE;
	}

	while (mainWindow.IsGameWindowOpen())
	{
		mainWindow.RunMainGameLoop();
	}

	return EXIT_SUCCESS;
}