#ifndef MAINRENDERWINDOW_H
#define MAINRENDERWINDOW_H

#include <SFML/Graphics.hpp>

namespace Pong
{
	/// <summary>
	/// Creates and controls Main Window
	/// </summary>
	class MainRenderWindow
	{
	public:
		MainRenderWindow();
		~MainRenderWindow();
		//Checks if Game Window is open
		const bool IsGameWindowOpen() const;
		//Main Game Loop
		void UpdateGame();

		//Main Renderer Loop
		//void RenderUpdate();
	private:
		//Main Renderer Loop
		void RenderUpdate();

		//Closes the Main Game Window
		void QuitGame();
		//Render Window Variable Reference
		sf::RenderWindow* mainRenderWindow = nullptr;
		//Video Mode Varaible Reference
		sf::VideoMode videoMode;
		//Event Getter Variable
		sf::Event eventRef;
	};
}
#endif