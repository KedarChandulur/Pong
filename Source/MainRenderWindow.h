#ifndef MAINRENDERWINDOW_H
#define MAINRENDERWINDOW_H

//#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

namespace Pong
{
	struct InGameContraints
	{
		const float pi = 3.14159f;
		const float defaultSpeed = 200.0f;

		const float defaultWindowWidth = 960.0f;
		const float defaultWindowHeight = 720.0f;
	};

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
		//Updates in game element properities/in game element activity on every main() iteration.
		//void UpdateInGameElements();
		//Main Renderer Loop
		void RenderUpdate();
		//Closes the Main Game Window
		void QuitGame();
		//Initializes required resources
		void LoadBackground();
		//Initializes in game elements - Paddles and ball.
		void LoadInGameElements();

		//Render Window Variable Reference
		sf::RenderWindow* mainRenderWindow = nullptr;
		//Video Mode Varaible Reference
		sf::VideoMode videoMode;
		//Event Getter Variable
		sf::Event eventRef;
		//Background Sprite
		sf::Sprite bgSprite;
		//Background Texture
		sf::Texture bgTexture;
		/*sf::RectangleShape bgSprite;*/

		//InGameContraints Struct Holder
		InGameContraints inGameContraints;

		//Clock Reference
		sf::Clock clock;

		//In Game Elements
		Paddle leftPaddle_Ref;
		Paddle rightPaddle_Ref;
		Ball ball_Ref;

		//sf::RectangleShape leftPaddle;
		//sf::RectangleShape rightPaddle;
		//sf::CircleShape ball;

		//InGameContraints Struct Holder
		//InGameContraints inGameContraints;
	};
}
#endif