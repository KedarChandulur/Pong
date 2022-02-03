#include "Application.h"

Pong::Application::Application()
{
	mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::GlobalVariables::SCREEN_WIDTH, Pong::GlobalVariables::SCREEN_HEIGHT, 32U), "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	mainRenderWindow->setVerticalSyncEnabled(true);
}

Pong::Application::~Application()
{
	CleanUp();
}

void Pong::Application::QuitGame()
{
	mainRenderWindow->close();
}

bool Pong::Application::Initialize()
{
	return commonElementsHandler.Init(*mainRenderWindow);
}

void Pong::Application::CleanUp()
{
	delete mainRenderWindow;
}

void Pong::Application::RunMainGameLoop()
{
	sf::Clock clock = sf::Clock();
	float deltaTime = 0.0f;
	while (mainRenderWindow->isOpen())
	{
		//float deltaTime = clock.restart().asSeconds();
		deltaTime = clock.restart().asSeconds();
		ProcessEvents(deltaTime, clock);
		Update(deltaTime);
		Render();
	}
}

void Pong::Application::ProcessEvents(const float& deltaTime, sf::Clock& clock)
{
	sf::Event eventRef;

	while (mainRenderWindow->pollEvent(eventRef))
	{
		switch (eventRef.type)
		{
		case sf::Event::EventType::Closed:
			QuitGame();
			break;
		case sf::Event::EventType::KeyPressed:
			if (eventRef.key.code == sf::Keyboard::Escape)
			{
				if (Pong::GlobalVariables::inGame)
				{
					//Go to main menu.
					Pong::GlobalVariables::inGame = false;
					commonElementsHandler.GetMainTextRef().setString("Hello, Welcome to Pong");
					commonElementsHandler.startgame_Text.GetTextRef().setString("Start");
				}
				else
				{
					QuitGame();
				}
				break;
			}
			else if (eventRef.key.code == sf::Keyboard::Enter)
			{
				if (!Pong::GlobalVariables::inGame)
				{
					//Start or Restart a game.
					commonElementsHandler.startgame_Text.GetTextRef().setString("Restart");
					if (commonElementsHandler.startgame_Text.GetIsSelected())
					{
						Pong::GlobalVariables::inGame = true;

						clock.restart();

						ball_Ref.SetRandomAngle();
						leftPaddle_Ref.Init(true);
						rightPaddle_Ref.Init(false);
						ball_Ref.Init();
						commonElementsHandler.PlayBallAudio();
					}
					else if (commonElementsHandler.quitgame_Text.GetIsSelected())
					{
						QuitGame();
					}
					break;
				}
			}
			else if (eventRef.key.code == sf::Keyboard::C)
			{
				//Toggling only works in main menu
				if (!Pong::GlobalVariables::inGame)
				{
					//Toggle the AI -> manual mode or vice versa.
					rightPaddle_Ref.playAgainstAI = !rightPaddle_Ref.playAgainstAI;
					if (!rightPaddle_Ref.playAgainstAI)
					{
						commonElementsHandler.playmode.GetTextRef().setString("P v P");
						rightPaddle_Ref.ReValidateManualSpeed();
					}
					else
					{
						commonElementsHandler.playmode.GetTextRef().setString("P v C");
						rightPaddle_Ref.ResetSpeed();
					}
					commonElementsHandler.PlayBallAudio();
				}
			}


			if (rightPaddle_Ref.playAgainstAI)
			{
				//Set AI difficulty
				if (eventRef.key.code == sf::Keyboard::Num1 || eventRef.key.code == sf::Keyboard::Numpad1)
				{
					rightPaddle_Ref.SetAIDifficulty(static_cast<uint16_t>(Pong::GlobalEnums::DifficultyLevel::Low));
				}
				else if (eventRef.key.code == sf::Keyboard::Num2 || eventRef.key.code == sf::Keyboard::Numpad2)
				{
					rightPaddle_Ref.SetAIDifficulty(static_cast<uint16_t>(Pong::GlobalEnums::DifficultyLevel::Medium));
				}
				else if (eventRef.key.code == sf::Keyboard::Num3 || eventRef.key.code == sf::Keyboard::Numpad3)
				{
					rightPaddle_Ref.SetAIDifficulty(static_cast<uint16_t>(Pong::GlobalEnums::DifficultyLevel::High));
				}
				else if (eventRef.key.code == sf::Keyboard::Num4 || eventRef.key.code == sf::Keyboard::Numpad4)
				{
					rightPaddle_Ref.SetAIDifficulty(static_cast<uint16_t>(Pong::GlobalEnums::DifficultyLevel::VeryHigh));
				}
			}

			if (!Pong::GlobalVariables::inGame)
			{
				//Navigation controls in main menu or restart menu.
				if (eventRef.key.code == sf::Keyboard::Up)
				{
					commonElementsHandler.PlayBallAudio();
					commonElementsHandler.startgame_Text.SetIsSelected(!commonElementsHandler.startgame_Text.GetIsSelected());
					commonElementsHandler.quitgame_Text.SetIsSelected(!commonElementsHandler.quitgame_Text.GetIsSelected());
				}
				else if (eventRef.key.code == sf::Keyboard::Down)
				{
					commonElementsHandler.PlayBallAudio();
					commonElementsHandler.startgame_Text.SetIsSelected(!commonElementsHandler.startgame_Text.GetIsSelected());
					commonElementsHandler.quitgame_Text.SetIsSelected(!commonElementsHandler.quitgame_Text.GetIsSelected());
				}
			}
			else
			{
				//Player - 1 move controls.
				if (eventRef.key.code == sf::Keyboard::W)
				{
					leftPaddle_Ref.MoveUp(deltaTime);
				}
				else if (eventRef.key.code == sf::Keyboard::S)
				{
					leftPaddle_Ref.MoveDown(deltaTime);
				}
				//Player - 2 move controls.
				else if (eventRef.key.code == sf::Keyboard::Up)
				{
					if (!rightPaddle_Ref.playAgainstAI)
						rightPaddle_Ref.MoveUp(deltaTime);
				}
				else if (eventRef.key.code == sf::Keyboard::Down)
				{
					if (!rightPaddle_Ref.playAgainstAI)
						rightPaddle_Ref.MoveDown(deltaTime);
				}
			}

			break;
		}
	}
}

void Pong::Application::Update(const float& deltaTime)
{
	if (Pong::GlobalVariables::inGame)
	{
		//Left and right boundry collision check
		if (ball_Ref.CheckForRight_BoundryCollision())
		{
			Pong::GlobalVariables::inGame = false;
			commonElementsHandler.GetMainTextRef().setString("\n\t\tPlayer-1 wins!\n");
		}
		else if (ball_Ref.CheckForLeft_BoundryCollision())
		{
			Pong::GlobalVariables::inGame = false;
			commonElementsHandler.GetMainTextRef().setString("\n\t\tPlayer-2 wins!\n");
		}

		//Updating AI paddle movement based on AI mode(is on or off).
		if (rightPaddle_Ref.playAgainstAI)
			rightPaddle_Ref.UpdateAIPaddleMovement(ball_Ref, deltaTime);

		//Top and Bottom boundry collision check
		ball_Ref.CheckForTopAndBottom_BoundryCollision(deltaTime);

		//Left and right paddle collision check
		ball_Ref.CheckForLeftPaddleCollision(leftPaddle_Ref, commonElementsHandler);
		ball_Ref.CheckForRightPaddleCollision(rightPaddle_Ref, commonElementsHandler);
	}
}

void Pong::Application::Render()
{
	//Clearing previous frame/window
	mainRenderWindow->clear();

	//Main-menu text | In-Game Background sprite based on the game state.
	commonElementsHandler.Render(*mainRenderWindow);

	if (Pong::GlobalVariables::inGame)
	{
		//Rendering paddles and ball
		leftPaddle_Ref.Render(*mainRenderWindow);
		rightPaddle_Ref.Render(*mainRenderWindow);
		ball_Ref.Render(*mainRenderWindow);
	}

	//Rendering the window(Rendering new/current frame)
	mainRenderWindow->display();
}