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
		//On false(failure) app will be terminated.
		bool Initialize();

		//Main Game Loop
		void RunMainGameLoop();

		const bool IsGameWindowOpen() const;
	private:
		//Process input events
		void ProcessEvents(const float& deltaTime);
		//Main Update Loop
		void Update(const float& deltaTime);
		//Main Render Loop
		void Render();
		void QuitGame();

		//Main Render Window Reference
		sf::RenderWindow* mainRenderWindow = nullptr;		
		sf::Clock clock;

		CommonElementsHandler commonElementsHandler;
		Paddle leftPaddle_Ref;
		Paddle rightPaddle_Ref;
		Ball ball_Ref;
	};
}
#endif