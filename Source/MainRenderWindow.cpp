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
					inGame = false;
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
					commonElementsHandler.startgame_Text.GetTextRef().setString("Restart");
					if (commonElementsHandler.startgame_Text.GetIsSelected())
					{
						Pong::inGame = true;
						clock.restart();

						//leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
						//rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);
						leftPaddle_Ref.Init(true);
						rightPaddle_Ref.Init(false);

						ball_Ref.Init();
						ball_Ref.SetRandomAngle();
						commonElementsHandler.GetSoundObject().play();
						/*auto playsound = commonElementsHandler.GetSoundObject();
						playsound.play();*/
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
				rightPaddle_Ref.playAgainstAI = !rightPaddle_Ref.playAgainstAI;
				if (!rightPaddle_Ref.playAgainstAI)
					rightPaddle_Ref.ValidateManualSpeed();
				else
					rightPaddle_Ref.ResetSpeed();
			}

			if (rightPaddle_Ref.playAgainstAI)
			{
				if (eventRef.key.code == sf::Keyboard::Num1 || eventRef.key.code == sf::Keyboard::Numpad1)
				{
					//rightPaddle_Ref.UpdateAIPaddleSpeedEnum(1);
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::Low);
				}
				else if (eventRef.key.code == sf::Keyboard::Num2 || eventRef.key.code == sf::Keyboard::Numpad2)
				{
					//rightPaddle_Ref.UpdateAIPaddleSpeedEnum(2);
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::Medium);
				}
				else if (eventRef.key.code == sf::Keyboard::Num3 || eventRef.key.code == sf::Keyboard::Numpad3)
				{
					//rightPaddle_Ref.UpdateAIPaddleSpeedEnum(3);
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::High);
				}
				else if (eventRef.key.code == sf::Keyboard::Num4 || eventRef.key.code == sf::Keyboard::Numpad4)
				{
					//rightPaddle_Ref.UpdateAIPaddleSpeedEnum(4);
					rightPaddle_Ref.UpdateAIPaddleSpeedEnum(Pong::GlobalEnums::DifficultyLevel::VeryHigh);
				}
			}

			if (!inGame)
			{
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
				if (eventRef.key.code == sf::Keyboard::W)
				{
					leftPaddle_Ref.MoveUp(deltaTime);
				}
				else if (eventRef.key.code == sf::Keyboard::S)
				{
					leftPaddle_Ref.MoveDown(deltaTime);
				}
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

		if (rightPaddle_Ref.playAgainstAI)
			ball_Ref.UpdateAIPaddleMovement(rightPaddle_Ref, deltaTime);

		ball_Ref.CheckForTopAndBottom_BoundryCollision(deltaTime);
		if (ball_Ref.CheckForLeftPaddleCollision(leftPaddle_Ref))
		{
			commonElementsHandler.GetSoundObject().play();
		}
		if (ball_Ref.CheckForRightPaddleCollision(rightPaddle_Ref))
		{
			commonElementsHandler.GetSoundObject().play();
		}
	}
}

void Pong::MainRenderWindow::Render()
{
	//Clearing previous frame/window
	mainRenderWindow->clear();

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