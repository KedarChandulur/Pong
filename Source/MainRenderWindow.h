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
		void RunMainGameLoop();

		//Checks if Game Window is open
		const bool IsGameWindowOpen() const;
	private:
		//Process basic input events
		void ProcessEvents(const float& deltaTime);
		//Main Update Loop
		void Update(const float& deltaTime);
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
	};
}
#endif