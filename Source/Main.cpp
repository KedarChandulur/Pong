#include "MainRenderWindow.h"

int main()
{
	Pong::MainRenderWindow mainWindow;

	if (!mainWindow.Initialize())
	{
		return EXIT_FAILURE;
	}

	while (mainWindow.IsGameWindowOpen())
	{
		mainWindow.UpdateGame();
	}

	return EXIT_SUCCESS;
}