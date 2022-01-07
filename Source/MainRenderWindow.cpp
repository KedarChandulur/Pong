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
	leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
	rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);

	//Ball Initialization
	ball_Ref.Init();
	return true;
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
	float deltaTime = clock.restart().asSeconds();

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
				if (!inGame)
				{
					inGame = true;
					clock.restart();

					leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
					rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);

					ball_Ref.Init();
					ball_Ref.SetRandomAngle();
				}
			}

			if (inGame)
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
					rightPaddle_Ref.MoveUp(deltaTime);
				}
				else if (eventRef.key.code == sf::Keyboard::Down)
				{
					rightPaddle_Ref.MoveDown(deltaTime);
				}
			}

			break;
		case sf::Event::EventType::Resized:
			SCREEN_WIDTH = static_cast<unsigned short>(eventRef.size.width);
			SCREEN_HEIGHT = static_cast<unsigned short>(eventRef.size.height);

			commonElementsHandler.UpdateBGSpriteScaleBasedOnRes();
			break;
		}
	}

	if (inGame)
	{
		if (ball_Ref.CheckForRight_BoundryCollision())
		{
			inGame = false;
			commonElementsHandler.GetMainTextRef().setString("Player-1 wins!\nPress space to restart or\nescape to exit");
		}
		else if (ball_Ref.CheckForLeft_BoundryCollision())
		{
			inGame = false;
			commonElementsHandler.GetMainTextRef().setString("Player-2 wins!\nPress space to restart or\nescape to exit");
		}

		ball_Ref.CheckForTopAndBottom_BoundryCollision(deltaTime);
		ball_Ref.CheckForLeftPaddleCollision(leftPaddle_Ref);
		ball_Ref.CheckForRightPaddleCollision(rightPaddle_Ref);
	}

	Render();
}

void Pong::MainRenderWindow::Render()
{
	//Clearing previous frame/window
	mainRenderWindow->clear();
	//Drawing background sprite(based on menu or ingame).

	if (!inGame)
	{
		//Drawing menu background sprite.
		mainRenderWindow->draw(commonElementsHandler.GetMainTextRef());
	}
	else
	{
		mainRenderWindow->draw(commonElementsHandler.GetBGSpriteRef());
		//Rendering paddles and ball
		mainRenderWindow->draw(leftPaddle_Ref.GetMainPaddleRef());
		mainRenderWindow->draw(rightPaddle_Ref.GetMainPaddleRef());
		mainRenderWindow->draw(ball_Ref.GetMainBallRef());
	}

	//Rendering the window(Rendering new/current frame)
	mainRenderWindow->display();
}