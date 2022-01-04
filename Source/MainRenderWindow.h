#ifndef MAINRENDERWINDOW_H
#define MAINRENDERWINDOW_H

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
		//Main Game Loop
		void UpdateGame();

		//Checks if Game Window is open
		const bool IsGameWindowOpen() const;
	private:
		//Main Renderer Loop
		void Render();
		//Closes the Main Game Window
		void QuitGame();
		//Initializes required resources
		void LoadBackground();
		//Initializes in game elements - Paddles and ball.
		void LoadInGameElements();

		//Render Window Variable Reference
		sf::RenderWindow* mainRenderWindow = nullptr;
		//Event Getter Variable
		sf::Event eventRef;
		//Background Sprite
		sf::Sprite bgSprite;
		//Background Texture
		sf::Texture bgTexture;
		/*sf::RectangleShape bgSprite;*/

		//Clock Reference
		sf::Clock clock;

		//In Game Elements
		Paddle leftPaddle_Ref;
		Paddle rightPaddle_Ref;
		Ball ball_Ref;
	};
}
#endif