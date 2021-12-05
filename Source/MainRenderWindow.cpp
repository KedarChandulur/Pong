#include <iostream>
#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	this->videoMode.width = 960;
	this->videoMode.height = 720;
	//this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Default);
	this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	this->mainRenderWindow->setVerticalSyncEnabled(true);
	LoadBackground();
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
	bgTexture.create(videoMode.width, videoMode.height);
	if (bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{
		std::cout << "Background texture loaded successfully.\n";
		this->bgSprite.setTexture(bgTexture);
	}
	else
	{
		std::cout << "Error loading the background texture.\n";
	}
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return this->mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
	//Not using "pollEvent()" - instead using "waitEvent()" and waiting for some event to be triggered.
	while (this->mainRenderWindow->waitEvent(this->eventRef))
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
			else if (this->eventRef.key.code == sf::Keyboard::Space)
			{
				break;
			}
		case sf::Event::EventType::MouseButtonPressed:

			break;
		case sf::Event::EventType::MouseButtonReleased:

			break;
		}

		RenderUpdate();
	}
}

void Pong::MainRenderWindow::RenderUpdate()
{
	//Clearing everything with a solid color.(Clearing previous frame)
	this->mainRenderWindow->clear();

	//Drawing background sprite.
	this->mainRenderWindow->draw(bgSprite);

	//Rendering the window(Rendering new/current frame)
	this->mainRenderWindow->display();
}