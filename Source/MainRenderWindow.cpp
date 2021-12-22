#include <iostream>
//#include <ctime>
#include "MainRenderWindow.h"

Pong::MainRenderWindow::MainRenderWindow()
{
	this->videoMode.width = inGameContraints.defaultWindowWidth;
	this->videoMode.height = inGameContraints.defaultWindowHeight;
	this->videoMode.bitsPerPixel = 32U;
	//this->mainRenderWindow = new sf::RenderWindow(this->videoMode, "Pong Game", sf::Style::Default);
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
	sf::Vector2f paddleSize{ 25.0f, 100.0f };
	//std::cout << this->videoMode.width / this->videoMode.height;	
	const float outLineThickness = 2.5f;

	this->leftPaddle_Ref.Init(inGameContraints.defaultSpeed, sf::Color::Green,videoMode, 0.05f);
	this->rightPaddle_Ref.Init(inGameContraints.defaultSpeed, sf::Color::Red, videoMode, 0.925f);
	this->ball_Ref.Init(videoMode.width, videoMode.height, inGameContraints.pi);
	//this->leftPaddle.setSize(paddleSize - sf::Vector2f(outLineThickness, outLineThickness));
	//this->rightPaddle.setSize(paddleSize - sf::Vector2f(outLineThickness, outLineThickness));

	//this->leftPaddle.setOutlineThickness(outLineThickness);
	//this->rightPaddle.setOutlineThickness(outLineThickness);

	//this->leftPaddle.setOutlineColor(sf::Color::Green);
	//this->rightPaddle.setOutlineColor(sf::Color::Red);

	////this->leftPaddle.setPosition(videoMode.width * 0.05f, videoMode.height / 2.f);
	////this->rightPaddle.setPosition(videoMode.width * 0.95f, videoMode.height / 2.f);

	//this->leftPaddle.setPosition(videoMode.width * 0.05f, videoMode.height / 2.f - (paddleSize.x * 2));
	//this->rightPaddle.setPosition(videoMode.width * 0.925f, videoMode.height / 2.f - (paddleSize.x * 2));

	//this->ball.setRadius(ballRadius);
	//this->ball.setPosition(videoMode.width / 2, videoMode.height / 2);

	////We are using "std::srand()" for creating randomness in initial ball angle/direction.
	////Initialise srand() using the current time for preventing srand to return same random value in different application instance(s).
	//std::srand(time(NULL));

	//float cosAngleValue = 0.0f;
	//float absValue = 0.0f;

	//// Keeping the ball angle/direction as horizontal as possible.
	//do
	//{
	//	auto rand = std::rand() % 360;
	//	std::cout << "rand: " << rand << std::endl;
	//	std::cout << "rand * 2: " << rand * 2 << std::endl;
	//	std::cout << "rand * 2 * pi: " << rand * 2 * inGameContraints.pi << std::endl;

	//	ballAngle = (rand) * 2 * inGameContraints.pi / 360;
	//	std::cout << "ballAngle: " << ballAngle << std::endl;

	//	cosAngleValue = std::cos(ballAngle);
	//	std::cout << "cosAngleValue: " << cosAngleValue << std::endl;
	//} while (std::abs(cosAngleValue) < 0.7f);
}

const bool Pong::MainRenderWindow::IsGameWindowOpen() const
{
	return this->mainRenderWindow->isOpen();
}

void Pong::MainRenderWindow::UpdateGame()
{
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
			else if (this->eventRef.key.code == sf::Keyboard::Space)
			{
				//float cosAngleValue = 0.0f;
				//float absValue = 0.0f;

				//// Keeping the ball angle/direction as horizontal as possible.
				//do
				//{
				//	auto rand = std::rand() % 360;
				//	std::cout << "rand: " << rand << std::endl;
				//	std::cout << "rand * 2: " << rand * 2 << std::endl;
				//	std::cout << "rand * 2 * pi: " << rand * 2 * inGameContraints.pi << std::endl;

				//	ballAngle = (rand) * 2 * inGameContraints.pi / 360;
				//	std::cout << "ballAngle: " << ballAngle << std::endl;

				//	cosAngleValue = std::cos(ballAngle);
				//	std::cout << "cosAngleValue: " << cosAngleValue << std::endl;
				//} while (std::abs(cosAngleValue) < 0.7f);

				break;
			}
		/*case sf::Event::EventType::Resized:
			
			break;*/
		/*case sf::Event::EventType::MouseButtonPressed:

			break;
		case sf::Event::EventType::MouseButtonReleased:

			break;*/		
		}
	}

	//float deltaTime = clock.restart().asSeconds();

	//UpdateInGameElements(inGameContraints.defaultSpeed * clock.restart().asSeconds());
	float deltaTime = inGameContraints.defaultSpeed * clock.restart().asSeconds();
	ball_Ref.Update(videoMode, deltaTime);
	//UpdateInGameElements();
	RenderUpdate();
}

//void Pong::MainRenderWindow::UpdateInGameElements()
//{
//	//Checking Right Border collision with ball
//	//Player-2/Right Paddle Wins
//	if (ball.getPosition().x - ballRadius < 0.0f)
//	{
//		//isPlaying = false;
//		//pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
//	}
//	//Checking Left Border collision with ball
//	//Player-1/Left Paddle Wins
//	if (ball.getPosition().x + ballRadius > this->videoMode.width)
//	{
//		//isPlaying = false;
//		//pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
//	}
//	//Checking Top Border collision with ball
//	if (ball.getPosition().y - ballRadius < 0.0f)
//	{
//		//ballSound.play();
//		ballAngle = -ballAngle;
//		//Offset for position.
//		ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
//	}
//	//Checking Button Border collision with ball
//	//if (ball.getPosition().y + ballRadius > gameHeight)
//	if (ball.getPosition().y + ballRadius > this->videoMode.height)
//	{
//		//ballSound.play();
//		ballAngle = -ballAngle;
//		//Offset for position.
//		ball.setPosition(ball.getPosition().x, this->videoMode.height - ballRadius - 0.1f);
//	}
//
//	//Using cos for determining x - move direction
//	//Using sin for determining y - move direction	
//	float deltaTime = inGameContraints.defaultSpeed * clock.restart().asSeconds();
//	ball.move(std::cos(ballAngle) * deltaTime, std::sin(ballAngle) * deltaTime);
//}

void Pong::MainRenderWindow::RenderUpdate()
{
	//Clearing everything with a solid color.(Clearing previous frame)
	this->mainRenderWindow->clear();

	//Drawing background sprite.
	this->mainRenderWindow->draw(bgSprite);

	//Rendering paddles and balls
	this->mainRenderWindow->draw(leftPaddle_Ref.mainPaddleShape);
	this->mainRenderWindow->draw(rightPaddle_Ref.mainPaddleShape);
	this->mainRenderWindow->draw(ball_Ref.mainCircleShape);

	//this->mainRenderWindow->draw(leftPaddle);
	//this->mainRenderWindow->draw(rightPaddle);
	//this->mainRenderWindow->draw(ball);

	//Rendering the window(Rendering new/current frame)
	this->mainRenderWindow->display();
}