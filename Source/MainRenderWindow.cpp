#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	//mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::SCREEN_WIDTH,Pong::SCREEN_HEIGHT,32U), "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	//mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::SCREEN_WIDTH,Pong::SCREEN_HEIGHT,32U), "Pong Game", sf::Style::Default);
	mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::SCREEN_WIDTH,Pong::SCREEN_HEIGHT,48U), "Pong Game", sf::Style::Default);
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
	if (!commonElementsHandler.Init(*mainRenderWindow))
		return false;

	//Paddle Initialization
	//leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
	//rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);
	leftPaddle_Ref.Init(true);
	rightPaddle_Ref.Init(false);

	//Ball Initialization
	ball_Ref.Init();
	return true;
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
				QuitGame();
				break;
			}
			else if (eventRef.key.code == sf::Keyboard::Space)
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
					}
				}
			}

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
				/*else if (eventRef.key.code == sf::Keyboard::Up)
				{
					rightPaddle_Ref.MoveUp(deltaTime);
				}
				else if (eventRef.key.code == sf::Keyboard::Down)
				{
					rightPaddle_Ref.MoveDown(deltaTime);
				}*/
			}

			break;
		case sf::Event::EventType::Resized:
			SCREEN_WIDTH = static_cast<unsigned short>(eventRef.size.width);
			SCREEN_HEIGHT = static_cast<unsigned short>(eventRef.size.height);

			commonElementsHandler.UpdateBGSpriteScaleBasedOnRes();
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
			commonElementsHandler.GetMainTextRef().setString("Player-1 wins!\nPress space to restart or\nescape to exit");
		}
		else if (ball_Ref.CheckForLeft_BoundryCollision())
		{
			Pong::inGame = false;
			commonElementsHandler.GetMainTextRef().setString("Player-2 wins!\nPress space to restart or\nescape to exit");
		}

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
	//Drawing background sprite(based on menu or ingame).

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