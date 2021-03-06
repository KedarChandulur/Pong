#include "Ball.h"

void Pong::Ball::Init()
{
	ballRadius = (float)(Pong::GlobalVariables::SCREEN_WIDTH / Pong::GlobalVariables::SCREEN_HEIGHT) * 10;
	
	this->mainBall.setRadius(ballRadius - outLineThickness);
	this->mainBall.setOutlineThickness(outLineThickness);
	this->mainBall.setOutlineColor(sf::Color::Cyan);

	this->mainBall.setOrigin(ballRadius / 2, ballRadius / 2);
	this->mainBall.setPosition(Pong::GlobalVariables::SCREEN_WIDTH / 2.0f, Pong::GlobalVariables::SCREEN_HEIGHT / 2.0f);
}

void Pong::Ball::SetRandomAngle()
{
	//We are using "std::srand()" for creating randomness in initial mainBall angle/direction.
	//Initialise srand() using the current time for preventing srand to return same random value in different application instance(s).
	//Using static cast to cast from 'time_t' to 'uint32_t(unsigned int)', preventing loss of data.
	std::srand(static_cast<uint32_t>(std::time(NULL)));

	float cosAngleValue = 0.0f;

	// Keeping the mainBall angle/direction as horizontal as possible.
	do
	{
		auto rand = std::rand() % 360;
		ballAngle = (rand) * 2 * pi / 360;
		cosAngleValue = std::cos(ballAngle);
	} while (std::abs(cosAngleValue) < 0.7f);
}

void Pong::Ball::CheckForTopAndBottom_BoundryCollision(const float& deltaTime)
{	
	//Checking Top Border collision with mainBall
	if (this->mainBall.getPosition().y - ballRadius < 0.0f)
	{
		ballAngle = -ballAngle;
		this->mainBall.setPosition(this->mainBall.getPosition().x, ballRadius - 0.1f);
	}

	//Checking Bottom Border collision with mainBall
	if (this->mainBall.getPosition().y + ballRadius > Pong::GlobalVariables::SCREEN_HEIGHT)
	{
		ballAngle = -ballAngle;
		this->mainBall.setPosition(this->mainBall.getPosition().x, Pong::GlobalVariables::SCREEN_HEIGHT - ballRadius);
	}

	//Using cos for determining x - move direction
	//Using sin for determining y - move direction	
	this->mainBall.move(std::cos(ballAngle) * speed * deltaTime, std::sin(ballAngle) * speed * deltaTime);
}

bool Pong::Ball::CheckForLeft_BoundryCollision() const
{
	if (this->mainBall.getPosition().x - ballRadius < 20.0f)
	{
		//Player-2/Right Paddle Wins
		return true;
	}

	return false;
}

bool Pong::Ball::CheckForRight_BoundryCollision() const
{
	if (this->mainBall.getPosition().x + ballRadius > Pong::GlobalVariables::SCREEN_WIDTH - 25.0f)
	{
		//Player-1/Left Paddle Wins
		return true;
	}

	return false;
}

void Pong::Ball::Render(sf::RenderWindow& mainRenderWindow)
{
	mainRenderWindow.draw(mainBall);
}

const sf::CircleShape& Pong::Ball::GetMainBall() const
{
	return mainBall;
}

const float& Pong::Ball::GetRadius() const
{
	return ballRadius;
}

void Pong::Ball::CheckForLeftPaddleCollision(const Pong::Paddle& leftPaddle, Pong::CommonElementsHandler& commonElementsHandler)
{
	if (mainBall.getPosition().x < leftPaddle.GetMainPaddleRef().getPosition().x + leftPaddle.GetPaddleSize().x / 2 &&
		mainBall.getPosition().x - ballRadius > leftPaddle.GetMainPaddleRef().getPosition().x &&
		mainBall.getPosition().y + ballRadius >= leftPaddle.GetMainPaddleRef().getPosition().y - leftPaddle.GetPaddleSize().y / 2 &&
		mainBall.getPosition().y - ballRadius <= leftPaddle.GetMainPaddleRef().getPosition().y + leftPaddle.GetPaddleSize().y / 2)
	{
		if (mainBall.getPosition().y > leftPaddle.GetMainPaddleRef().getPosition().y)
			ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
		else
			ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

		mainBall.setPosition(leftPaddle.GetMainPaddleRef().getPosition().x + ballRadius + leftPaddle.GetPaddleSize().x / 2 + 0.1f, mainBall.getPosition().y);
		commonElementsHandler.PlayBallAudio();
	}
}

void Pong::Ball::CheckForRightPaddleCollision(const Pong::Paddle& rightPaddle, Pong::CommonElementsHandler& commonElementsHandler)
{
	if (mainBall.getPosition().x + ballRadius > rightPaddle.GetMainPaddleRef().getPosition().x - rightPaddle.GetPaddleSize().x / 2 &&
		mainBall.getPosition().x + ballRadius < rightPaddle.GetMainPaddleRef().getPosition().x &&
		mainBall.getPosition().y + ballRadius >= rightPaddle.GetMainPaddleRef().getPosition().y - rightPaddle.GetPaddleSize().y / 2 &&
		mainBall.getPosition().y - ballRadius <= rightPaddle.GetMainPaddleRef().getPosition().y + rightPaddle.GetPaddleSize().y / 2)
	{
		if (mainBall.getPosition().y > rightPaddle.GetMainPaddleRef().getPosition().y)
			ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
		else
			ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

		mainBall.setPosition(rightPaddle.GetMainPaddleRef().getPosition().x - ballRadius - rightPaddle.GetPaddleSize().x / 2 - 0.1f, mainBall.getPosition().y);
		commonElementsHandler.PlayBallAudio();
	}
}