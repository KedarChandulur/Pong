#include "MainRenderWindow.h"

int main()
{
	Pong::MainRenderWindow mainWindow;

	while (mainWindow.IsGameWindowOpen())
	{
		mainWindow.UpdateGame();
	}

	return 0;
}