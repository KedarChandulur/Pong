#ifndef MAINRENDERWINDOW_H
#define MAINRENDERWINDOW_H

#include <SFML/Graphics.hpp>

/// <summary>
/// Creates and controls Main Window
/// </summary>
class MainRenderWindow
{
public:
	MainRenderWindow();
	~MainRenderWindow();
	//Checks if Game is running(Returns true if window is open and false if closed)
	const bool IsGameRunning() const;
	//Main Game Loop
	void UpdateGame();
private:
	//Closes the Main Game Window
	void QuitGame();
	//Render Window Variable Reference
	sf::RenderWindow* mainRenderWindow = nullptr;
	//Video Mode Varaible Reference
	sf::VideoMode videoMode;
	//Event Getter Variable
	sf::Event eventRef;
};
#endif