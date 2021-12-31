#include "Ball.h"

void Pong::Ball::Init(const float& width, const float& height)
{
	ballRadius = (float)(width / height) * 10;

	this->mainCircleShape.setRadius(ballRadius);
	this->mainCircleShape.setPosition(width / 2, height / 2);

	//We are using "std::srand()" for creating randomness in initial ball angle/direction.
	//Initialise srand() using the current time for preventing srand to return same random value in different application instance(s).
	std::srand(time(NULL));

	float cosAngleValue = 0.0f;

	// Keeping the ball angle/direction as horizontal as possible.
	do
	{
		auto rand = std::rand() % 360;
		ballAngle = (rand) * 2 * pi / 360;
		cosAngleValue = std::cos(ballAngle);		
	} while (std::abs(cosAngleValue) < 0.7f);
}

void Pong::Ball::Update(const sf::VideoMode& videoMode, const float& deltaTime)
{	
	//Checking Top Border collision with ball
	if (this->mainCircleShape.getPosition().y - ballRadius < 0.0f)
	{
		//ballSound.play();
		ballAngle = -ballAngle;
		//Offset for position.
		//this->mainCircleShape.setPosition(this->mainCircleShape.getPosition().x, ballRadius - 0.1f);
		this->mainCircleShape.setPosition(this->mainCircleShape.getPosition().x, ballRadius);
	}
	//Checking Button Border collision with ball
	//if (ball.getPosition().y + ballRadius > gameHeight)
	if (this->mainCircleShape.getPosition().y + ballRadius > videoMode.height)
	{
		//ballSound.play();
		ballAngle = -ballAngle;
		//Offset for position.
		this->mainCircleShape.setPosition(this->mainCircleShape.getPosition().x, videoMode.height - (ballRadius));
	}

	//float deltaTime = inGameContraints.defaultSpeed * clock.restart().asSeconds();
	//Using cos for determining x - move direction
	//Using sin for determining y - move direction	
	this->mainCircleShape.move(std::cos(ballAngle) * speed * deltaTime, std::sin(ballAngle) * speed * deltaTime);
}

bool Pong::Ball::CheckForLeft_BoundryCollision()
{
	if (this->mainCircleShape.getPosition().x - ballRadius < 0.0f)
	{
		//Player-1/Left Paddle Wins
		return true;
	}

	return false;
}

bool Pong::Ball::CheckForRight_BoundryCollision(const float& screenWidth)
{
	if (this->mainCircleShape.getPosition().x + ballRadius > screenWidth - 25.0f)
	{
		//Player-2/Right Paddle Wins
		return true;		
	}

	return false;
}

void Pong::Ball::CheckForLeftPaddleCollision(const Pong::Paddle& leftPaddle)
{
	// Check the collisions between the ball and the paddles
	// Left Paddle
	if (mainCircleShape.getPosition().x - ballRadius < leftPaddle.mainPaddleShape.getPosition().x + leftPaddle.paddleSize.x / 2 &&
		mainCircleShape.getPosition().x - ballRadius > leftPaddle.mainPaddleShape.getPosition().x &&
		mainCircleShape.getPosition().y + ballRadius >= leftPaddle.mainPaddleShape.getPosition().y - leftPaddle.paddleSize.y / 4 &&
		mainCircleShape.getPosition().y - ballRadius <= leftPaddle.mainPaddleShape.getPosition().y + leftPaddle.paddleSize.y)

		//mainCircleShape.getPosition().y - ballRadius >= leftPaddle.mainPaddleShape.getPosition().y - leftPaddle.paddleSize.y / 2 &&
		//mainCircleShape.getPosition().y + ballRadius <= leftPaddle.mainPaddleShape.getPosition().y + leftPaddle.paddleSize.y / 2)

		//mainCircleShape.getPosition().y + ballRadius >= leftPaddle.mainPaddleShape.getPosition().y - leftPaddle.paddleSize.y / 2 &&
		//mainCircleShape.getPosition().y - ballRadius <= leftPaddle.mainPaddleShape.getPosition().y + leftPaddle.paddleSize.y / 2)
	{
		if (mainCircleShape.getPosition().y > leftPaddle.mainPaddleShape.getPosition().y)
			ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
		else
			ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

		//ballSound.play();
		mainCircleShape.setPosition(leftPaddle.mainPaddleShape.getPosition().x + ballRadius + leftPaddle.paddleSize.x / 2 + 0.1f, mainCircleShape.getPosition().y);
	}
}

void Pong::Ball::CheckForRightPaddleCollision(const Pong::Paddle& rightPaddle)
{
	// Right Paddle
	if (mainCircleShape.getPosition().x + ballRadius > rightPaddle.mainPaddleShape.getPosition().x - rightPaddle.paddleSize.x / 2 &&
		mainCircleShape.getPosition().x + ballRadius < rightPaddle.mainPaddleShape.getPosition().x &&
		mainCircleShape.getPosition().y + ballRadius >= rightPaddle.mainPaddleShape.getPosition().y - rightPaddle.paddleSize.y / 4 &&
		mainCircleShape.getPosition().y - ballRadius <= rightPaddle.mainPaddleShape.getPosition().y + rightPaddle.paddleSize.y)

		//mainCircleShape.getPosition().y - ballRadius >= rightPaddle.mainPaddleShape.getPosition().y - rightPaddle.paddleSize.y / 2 &&
		//mainCircleShape.getPosition().y + ballRadius <= rightPaddle.mainPaddleShape.getPosition().y + rightPaddle.paddleSize.y / 2)

		//mainCircleShape.getPosition().y + ballRadius >= rightPaddle.mainPaddleShape.getPosition().y - rightPaddle.paddleSize.y / 2 &&
		//mainCircleShape.getPosition().y - ballRadius <= rightPaddle.mainPaddleShape.getPosition().y + rightPaddle.paddleSize.y / 2)
	{
		if (mainCircleShape.getPosition().y > rightPaddle.mainPaddleShape.getPosition().y)
			ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
		else
			ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

		//ballSound.play();
		mainCircleShape.setPosition(rightPaddle.mainPaddleShape.getPosition().x - ballRadius - rightPaddle.paddleSize.x / 2 - 0.1f, mainCircleShape.getPosition().y);
	}
}