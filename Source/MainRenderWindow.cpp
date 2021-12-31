#include <iostream>
#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	this->videoMode.width = 960.0f;
	this->videoMode.height = 720.0f;
	this->videoMode.bitsPerPixel = 32U;
	this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Titlebar | sf::Style::Close);	
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

	this->bgTexture.create(this->videoMode.width, this->videoMode.height);
	//this->bgTexture.create(bgImage.getSize().x, bgImage.getSize().y);

	//if (this->bgTexture.loadFromImage(bgImage))
	if (this->bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{		
		std::cout << "Background texture loaded successfully.\n";
		this->bgSprite.setTexture(bgTexture);
	}
	else
	{
		std::cout << "Error loading the background texture.\n";
	}
}

void Pong::MainRenderWindow::LoadInGameElements()
{
	this->leftPaddle_Ref.Init(sf::Color::Green,videoMode, 0.05f);
	this->rightPaddle_Ref.Init(sf::Color::Red, videoMode, 0.925f);
	this->ball_Ref.Init(videoMode.width, videoMode.height);
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return this->mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
	float deltaTime = clock.restart().asSeconds();

	while (this->mainRenderWindow->pollEvent(this->eventRef))
	{
		switch (this->eventRef.type)
		{
		case sf::Event::EventType::Closed:
			QuitGame();
			break;
		case sf::Event::EventType::KeyPressed:
			if (this->eventRef.key.code == sf::Keyboard::Escape)
			{
				QuitGame();
				break;
			}
			else if (this->eventRef.key.code == sf::Keyboard::W)
			{
				leftPaddle_Ref.MoveUp(deltaTime);
				//break;
			}
			else if (this->eventRef.key.code == sf::Keyboard::S)
			{
				leftPaddle_Ref.MoveDown(videoMode, deltaTime);				
				//break;
			}
			else if (this->eventRef.key.code == sf::Keyboard::Up)
			{				
				rightPaddle_Ref.MoveUp(deltaTime);
				//break;
			}
			else if (this->eventRef.key.code == sf::Keyboard::Down)
			{
				rightPaddle_Ref.MoveDown(videoMode, deltaTime);
				//break;
			}		
		}
	}

	if (ball_Ref.CheckForRight_BoundryCollision(videoMode.width))
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
	ball_Ref.Update(videoMode, deltaTime);
	ball_Ref.CheckForLeftPaddleCollision(leftPaddle_Ref);
	ball_Ref.CheckForRightPaddleCollision(rightPaddle_Ref);
	RenderUpdate();
}

void Pong::MainRenderWindow::RenderUpdate()
{
	//Clearing previous frame/window
	this->mainRenderWindow->clear();

	//Drawing background sprite.
	this->mainRenderWindow->draw(bgSprite);

	//Rendering paddles and ball
	this->mainRenderWindow->draw(leftPaddle_Ref.mainPaddleShape);
	this->mainRenderWindow->draw(rightPaddle_Ref.mainPaddleShape);
	this->mainRenderWindow->draw(ball_Ref.mainCircleShape);

	//Rendering the window(Rendering new/current frame)
	this->mainRenderWindow->display();
}