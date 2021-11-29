#include "MainRenderWindow.h"

int main()
{
	MainRenderWindow mainWindow;

	while (mainWindow.IsGameWindowOpen())
	{
		mainWindow.UpdateGame();
	}
}