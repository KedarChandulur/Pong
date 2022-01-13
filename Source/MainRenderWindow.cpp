#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::SCREEN_WIDTH, Pong::SCREEN_HEIGHT, 32U), "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	mainRenderWindow->setVerticalSyncEnabled(true);
}

Pong::MainRenderWindow::~MainRenderWindow()
{
	delete mainRenderWindow;
}

void Pong::MainRenderWindow::QuitGame()
{
	mainRenderWindow->close();
}

bool Pong::MainRenderWindow::Initialize()
{
	return commonElementsHandler.Init(*mainRenderWindow);
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::RunMainGameLoop()
{
	float deltaTime = clock.restart().asSeconds();
	ProcessEvents(deltaTime);
	Update(deltaTime);
	Render();
}

void Pong::MainRenderWindow::ProcessEvents(const float& deltaTime)
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
				if (inGame)
				{
					//Go to main menu.
					inGame = false;
					commonElementsHandler.GetMainTextRef().setString("Hello, Welcome to Pong");
					commonElementsHandler.startgame_Text.GetTextRef().setString("Start");
				}
				else
				{
					QuitGame();
					break;
				}
			}
			else if (eventRef.key.code == sf::Keyboard::Enter)
			{
				if (!Pong::inGame)
				{
					//Start or Restart a game.
					commonElementsHandler.startgame_Text.GetTextRef().setString("Restart");
					if (commonElementsHandler.startgame_Text.GetIsSelected())
					{
						Pong::inGame = true;
						clock.restart();

						leftPaddle_Ref.Init(true);
						rightPaddle_Ref.Init(false);

						ball_Ref.Init();
						ball_Ref.SetRandomAngle();
						commonElementsHandler.GetSoundObject().play();
					}
					else if (commonElementsHandler.quitgame_Text.GetIsSelected())
					{
						QuitGame();
						break;
					}
				}
			}
			else if (eventRef.key.code == sf::Keyboard::C)
			{
				//Toggling only works in main menu
				if (!Pong::inGame)
				{
					//Toggle the AI -> manual mode or vice versa.
					rightPaddle_Ref.playAgainstAI = !rightPaddle_Ref.playAgainstAI;
					if (!rightPaddle_Ref.playAgainstAI)
					{
						commonElementsHandler.playmode.GetTextRef().setString("P v P");
						rightPaddle_Ref.ValidateManualSpeed();
					}
					else
					{
						commonElementsHandler.playmode.GetTextRef().setString("P v C");
						rightPaddle_Ref.ResetSpeed();
					}
				}
			}


			if (rightPaddle_Ref.playAgainstAI)
			{
				//Set AI difficulty
				if (eventRef.key.code == sf::Keyboard::Num1 || eventRef.key.code == sf::Keyboard::Numpad1)
				{
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::Low);
				}
				else if (eventRef.key.code == sf::Keyboard::Num2 || eventRef.key.code == sf::Keyboard::Numpad2)
				{
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::Medium);
				}
				else if (eventRef.key.code == sf::Keyboard::Num3 || eventRef.key.code == sf::Keyboard::Numpad3)
				{
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::High);
				}
				else if (eventRef.key.code == sf::Keyboard::Num4 || eventRef.key.code == sf::Keyboard::Numpad4)
				{
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::VeryHigh);
				}
			}

			if (!inGame)
			{
				//Navigation controls in main menu or restart menu.
				if (eventRef.key.code == sf::Keyboard::Up)
				{
					commonElementsHandler.GetSoundObject().play();
					commonElementsHandler.startgame_Text.SetIsSelected(!commonElementsHandler.startgame_Text.GetIsSelected());
					commonElementsHandler.quitgame_Text.SetIsSelected(!commonElementsHandler.quitgame_Text.GetIsSelected());
				}
				else if (eventRef.key.code == sf::Keyboard::Down)
				{
					commonElementsHandler.GetSoundObject().play();
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
					if(!rightPaddle_Ref.playAgainstAI)
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

void Pong::MainRenderWindow::Update(const float& deltaTime)
{
	if (Pong::inGame)
	{
		//Updating AI paddle movement based on AI mode(is on or off).
		if (rightPaddle_Ref.playAgainstAI)
			ball_Ref.UpdateAIPaddleMovement(rightPaddle_Ref, deltaTime);

		//Left and right paddle collision check
		if (ball_Ref.CheckForLeftPaddleCollision(leftPaddle_Ref))
		{
			commonElementsHandler.GetSoundObject().play();
		}
		else if (ball_Ref.CheckForRightPaddleCollision(rightPaddle_Ref))
		{
			commonElementsHandler.GetSoundObject().play();
		}

		//Left and right boundry collision check
		if (ball_Ref.CheckForRight_BoundryCollision())
		{
			Pong::inGame = false;
			commonElementsHandler.GetMainTextRef().setString("\n\t\tPlayer-1 wins!\n");
		}
		else if (ball_Ref.CheckForLeft_BoundryCollision())
		{
			Pong::inGame = false;
			commonElementsHandler.GetMainTextRef().setString("\n\t\tPlayer-2 wins!\n");
		}

		//Top and Bottom boundry collision check
		ball_Ref.CheckForTopAndBottom_BoundryCollision(deltaTime);
	}
}

void Pong::MainRenderWindow::Render()
{
	//Clearing previous frame/window
	mainRenderWindow->clear();

	//Main-menu text | In-Game Background sprite based on the game state.
	commonElementsHandler.Render(*mainRenderWindow);

	if(inGame)
	{
		//Rendering paddles and ball
		leftPaddle_Ref.Render(*mainRenderWindow);
		rightPaddle_Ref.Render(*mainRenderWindow);
		ball_Ref.Render(*mainRenderWindow);
	}

	//Rendering the window(Rendering new/current frame)
	mainRenderWindow->display();
}