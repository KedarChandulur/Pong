#include <iostream>
#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	this->videoMode.width = 960;
	this->videoMode.height = 720;
	this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	//this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
}

Pong::MainRenderWindow::~MainRenderWindow()
{
	delete this->mainRenderWindow;
}

void Pong::MainRenderWindow::QuitGame()
{
	this->mainRenderWindow->close();
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return this->mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
	//Not using poll event, using only wait event and waiting for some event to be triggered.
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
				std::cout << "Space Pressed\n";
				break;
			}
		case sf::Event::EventType::MouseButtonPressed:

			std::cout << "Mouse Pressed\n";
			break;
		case sf::Event::EventType::MouseButtonReleased:
			
			std::cout << "Mouse Released\n";
			break;
		}

		RenderUpdate();
	}
}

void Pong::MainRenderWindow::RenderUpdate()
{
	//Clearing everything with a solid color.(Clearing previous frame)
	this->mainRenderWindow->clear(sf::Color(255, 255, 0, 255));

	//Rendering the window(Rendering new/current frame)
	this->mainRenderWindow->display();
}