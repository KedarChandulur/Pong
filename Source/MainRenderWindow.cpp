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
	//sf::Image bgImage;

	/*if (bgImage.loadFromFile("Resources/Pong_BG.png"))
	{
		std::cout << "Image loaded.\n";
	}*/

	bgTexture.create(Pong::SCREEN_WIDTH, Pong::SCREEN_HEIGHT);
	//bgTexture.create(bgImage.getSize().x, bgImage.getSize().y);

	//if (bgTexture.loadFromImage(bgImage))
	if (bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{		
		//std::cout << "Background texture loaded successfully.\n";
		printf("Background texture loaded successfully.\n");
		bgSprite.setTexture(bgTexture);

		bgSprite.setScale(
			Pong::SCREEN_WIDTH / bgSprite.getLocalBounds().width,
			Pong::SCREEN_HEIGHT / bgSprite.getLocalBounds().height);

		//Paddle Initialization
		leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
		rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);

		//Ball Initialization
		ball_Ref.Init();

		return true;
	}
	else
	{
		//std::cout << "Error loading the background texture.\n";
		printf("Error loading the background texture.\n");
		return false;
	}
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
	float deltaTime = clock.restart().asSeconds();

	//sf::Event eventRef;

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
			else if (eventRef.key.code == sf::Keyboard::W)
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
	}

	if (ball_Ref.CheckForRight_BoundryCollision())
	{
		QuitGame();
		//isPlaying = false;
		//pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
	}
	else if (ball_Ref.CheckForLeft_BoundryCollision())
	{
		QuitGame();
		//isPlaying = false;
		//pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
	}

	ball_Ref.CheckForTopAndBottom_BoundryCollision(deltaTime);
	ball_Ref.CheckForLeftPaddleCollision(leftPaddle_Ref);
	ball_Ref.CheckForRightPaddleCollision(rightPaddle_Ref);
	Render();
}

void Pong::MainRenderWindow::Render()
{
	//Clearing previous frame/window
	mainRenderWindow->clear();

	//Drawing background sprite.
	mainRenderWindow->draw(bgSprite);

	//Rendering paddles and ball
	mainRenderWindow->draw(leftPaddle_Ref.GetMainPaddleRef());
	mainRenderWindow->draw(rightPaddle_Ref.GetMainPaddleRef());
	mainRenderWindow->draw(ball_Ref.GetMainBallRef());

	//Rendering the window(Rendering new/current frame)
	mainRenderWindow->display();
}