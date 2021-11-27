#include "MainRenderWindow.h"

int main()
{
	MainRenderWindow mainWindow;

	while (mainWindow.IsGameRunning())
	{
		mainWindow.UpdateGame();
	}
}