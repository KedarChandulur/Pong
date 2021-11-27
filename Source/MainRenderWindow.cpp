#include <iostream>
#include "MainRenderWindow.h"

//void MainRenderWindow::CreateWindowOnLoad()
MainRenderWindow::MainRenderWindow()
{
	this->videoMode.width = this->videoMode.height = 800;
	this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Titlebar | sf::Style::Close);
	//this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
}

MainRenderWindow::~MainRenderWindow()
{
	delete this->mainRenderWindow;
}

void MainRenderWindow::QuitGame()
{
	this->mainRenderWindow->close();
}

const bool MainRenderWindow::IsGameRunning() const
{
	return this->mainRenderWindow->isOpen();
}

void MainRenderWindow::UpdateGame()
{
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
			//this->mainRenderWindow-
			std::cout << "Pressed\n";
			break;
		case sf::Event::EventType::MouseButtonReleased:
			//this->mainRenderWindow-
			std::cout << "Released\n";
			break;
		}
	}
}