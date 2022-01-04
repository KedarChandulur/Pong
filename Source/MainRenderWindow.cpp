#include <iostream>
#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	//this->mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::SCREEN_WIDTH,Pong::SCREEN_HEIGHT,32U), "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	this->mainRenderWindow = new sf::RenderWindow(sf::VideoMode(Pong::SCREEN_WIDTH,Pong::SCREEN_HEIGHT,32U), "Pong Game", sf::Style::Default);
	this->mainRenderWindow->setVerticalSyncEnabled(true);
	LoadBackground();
	LoadInGameElements();
}

Pong::MainRenderWindow::~MainRenderWindow()
{
	delete this->mainRenderWindow;
}

void Pong::MainRenderWindow::QuitGame()
{
	this->mainRenderWindow->close();
}

void Pong::MainRenderWindow::LoadBackground()
{
	//sf::Image bgImage;

	/*if (bgImage.loadFromFile("Resources/Pong_BG.png"))
	{
		std::cout << "Image loaded.\n";
	}*/

	this->bgTexture.create(Pong::SCREEN_WIDTH, Pong::SCREEN_HEIGHT);
	//this->bgTexture.create(bgImage.getSize().x, bgImage.getSize().y);

	//if (this->bgTexture.loadFromImage(bgImage))
	if (this->bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{		
		std::cout << "Background texture loaded successfully.\n";
		this->bgSprite.setTexture(bgTexture);

		bgSprite.setScale(
			Pong::SCREEN_WIDTH / bgSprite.getLocalBounds().width,
			Pong::SCREEN_HEIGHT / bgSprite.getLocalBounds().height);
	}
	else
	{
		std::cout << "Error loading the background texture.\n";
	}
}

void Pong::MainRenderWindow::LoadInGameElements()
{
	this->leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
	this->rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);
	this->ball_Ref.Init();
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return this->mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
	float deltaTime = clock.restart().asSeconds();

	//sf::Event eventRef;

	while (this->mainRenderWindow->pollEvent(eventRef))
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
	this->mainRenderWindow->clear();

	//Drawing background sprite.
	this->mainRenderWindow->draw(bgSprite);

	//Rendering paddles and ball
	this->mainRenderWindow->draw(leftPaddle_Ref.GetMainPaddleRef());
	this->mainRenderWindow->draw(rightPaddle_Ref.GetMainPaddleRef());
	this->mainRenderWindow->draw(ball_Ref.GetMainBallRef());

	//Rendering the window(Rendering new/current frame)
	this->mainRenderWindow->display();
}