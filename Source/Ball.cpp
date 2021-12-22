#include "Ball.h"

void Ball::Init(const float& width, const float& height, const float& pi)
{
	ballRadius = (float)(width / height) * 10;

	this->mainCircleShape.setRadius(ballRadius);
	this->mainCircleShape.setPosition(width / 2, height / 2);

	//We are using "std::srand()" for creating randomness in initial ball angle/direction.
	//Initialise srand() using the current time for preventing srand to return same random value in different application instance(s).
	std::srand(time(NULL));

	float cosAngleValue = 0.0f;
	float absValue = 0.0f;

	// Keeping the ball angle/direction as horizontal as possible.
	do
	{
		auto rand = std::rand() % 360;
		ballAngle = (rand) * 2 * pi / 360;
		cosAngleValue = std::cos(ballAngle);		
	} while (std::abs(cosAngleValue) < 0.7f);
}

//void Ball::Update(const sf::VideoMode& videoMode, sf::Clock& clock)
void Ball::Update(const sf::VideoMode& videoMode, const float& deltaTime)
{
	//Checking Right Border collision with ball
	//Player-2/Right Paddle Wins
	if (this->mainCircleShape.getPosition().x - ballRadius < 0.0f)
	{
		//isPlaying = false;
		//pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
	}
	//Checking Left Border collision with ball
	//Player-1/Left Paddle Wins
	if (this->mainCircleShape.getPosition().x + ballRadius > videoMode.width)
	{
		//isPlaying = false;
		//pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
	}
	//Checking Top Border collision with ball
	if (this->mainCircleShape.getPosition().y - ballRadius < 0.0f)
	{
		//ballSound.play();
		ballAngle = -ballAngle;
		//Offset for position.
		this->mainCircleShape.setPosition(this->mainCircleShape.getPosition().x, ballRadius - 0.1f);
	}
	//Checking Button Border collision with ball
	//if (ball.getPosition().y + ballRadius > gameHeight)
	if (this->mainCircleShape.getPosition().y + ballRadius > videoMode.height)
	{
		//ballSound.play();
		ballAngle = -ballAngle;
		//Offset for position.
		this->mainCircleShape.setPosition(this->mainCircleShape.getPosition().x, videoMode.height - ballRadius + 0.1f);
	}

	//float deltaTime = inGameContraints.defaultSpeed * clock.restart().asSeconds();
	//Using cos for determining x - move direction
	//Using sin for determining y - move direction	
	this->mainCircleShape.move(std::cos(ballAngle) * deltaTime, std::sin(ballAngle) * deltaTime);
}