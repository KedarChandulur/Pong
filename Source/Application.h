#ifndef APPLICATION_H
#define APPLICATION_H

#include "Ball.h"

namespace Pong
{
	class Application
	{
		/// <summary>
		/// Creates and controls Main Window(Application)
		/// </summary>
	public:
		Application();
		~Application();

		//Initializes required resources
		//Returns true if Initialization was successfull.
		//On false(failure) app will be terminated.
		bool Initialize();

		//Main Game Loop
		void RunMainGameLoop();
	private:
		//Process input events
		void ProcessEvents(const float& deltaTime, sf::Clock& clock);
		//Main Update Loop
		void Update(const float& deltaTime);
		//Main Render Loop
		void Render();
		void QuitGame();

		//Main Render Window Reference
		sf::RenderWindow* mainRenderWindow = nullptr;

		CommonElementsHandler commonElementsHandler;
		Paddle leftPaddle_Ref;
		Paddle rightPaddle_Ref;
		Ball ball_Ref;
	};
}
#endif