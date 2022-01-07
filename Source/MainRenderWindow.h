#ifndef MAINRENDERWINDOW_H
#define MAINRENDERWINDOW_H

#include "CommonElementsHandler.h"
#include "Ball.h"

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

		//Initializes required resources
		//Returns true if Initialization was successfull.
		bool Initialize();

		//Main Game Loop
		void UpdateGame();

		//Checks if Game Window is open
		const bool IsGameWindowOpen() const;
	private:
		//Main Renderer Loop
		void Render();
		//Closes the Main Game Window
		void QuitGame();

		//Render Window Variable Reference
		sf::RenderWindow* mainRenderWindow = nullptr;
		
		//Clock Reference
		sf::Clock clock;

		//CommonElementsHandler Reference
		CommonElementsHandler commonElementsHandler;

		//In Game Elements
		Paddle leftPaddle_Ref;
		Paddle rightPaddle_Ref;
		Ball ball_Ref;

		bool inGame = false;
	};
}
#endif