#include "Ball.h"

void Pong::Ball::Init()
{
	ballRadius = (float)(Pong::SCREEN_WIDTH / Pong::SCREEN_HEIGHT) * 10;
	//ballRadius = 10;
	
	//this->mainBall.setRadius(ballRadius);

	this->mainBall.setRadius(ballRadius - outLineThickness);
	this->mainBall.setOutlineThickness(outLineThickness);
	this->mainBall.setOutlineColor(sf::Color::Cyan);

	this->mainBall.setOrigin(ballRadius / 2, ballRadius / 2);
	this->mainBall.setPosition(Pong::SCREEN_WIDTH / 2.0f, Pong::SCREEN_HEIGHT / 2.0f);	
}

void Pong::Ball::SetRandomAngle()
{
	//We are using "std::srand()" for creating randomness in initial mainBall angle/direction.
	//Initialise srand() using the current time for preventing srand to return same random value in different application instance(s).
	//Using static cast to cast from 'time_t' to 'unsigned int', preventing loss of data.
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	//std::srand(time(NULL));

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
		//ballSound.play();
		ballAngle = -ballAngle;
		//Offset for position.
		this->mainBall.setPosition(this->mainBall.getPosition().x, ballRadius - 0.1f);
	}
	//Checking Button Border collision with mainBall
	//if (mainBall.getPosition().y + ballRadius > gameHeight)
	if (this->mainBall.getPosition().y + ballRadius > Pong::SCREEN_HEIGHT)
	{
		//ballSound.play();
		ballAngle = -ballAngle;
		//Offset for position.
		this->mainBall.setPosition(this->mainBall.getPosition().x, Pong::SCREEN_HEIGHT - ballRadius);
	}

	//float deltaTime = inGameContraints.defaultSpeed * clock.restart().asSeconds();
	//Using cos for determining x - move direction
	//Using sin for determining y - move direction	
	this->mainBall.move(std::cos(ballAngle) * speed * deltaTime, std::sin(ballAngle) * speed * deltaTime);
}

const bool& Pong::Ball::CheckForLeft_BoundryCollision() const
{
	if (this->mainBall.getPosition().x - ballRadius < 20.0f)
	{
		//Player-1/Left Paddle Wins
		return true;
	}

	return false;
}

const bool& Pong::Ball::CheckForRight_BoundryCollision() const
{
	if (this->mainBall.getPosition().x + ballRadius > Pong::SCREEN_WIDTH - 25.0f)
	{
		//Player-2/Right Paddle Wins
		return true;		
	}

	return false;
}

void Pong::Ball::Render(sf::RenderWindow& mainRenderWindow) const
{
	mainRenderWindow.draw(mainBall);
}

//const void Pong::Ball::OnResizeEvent() const
//{
//
//}

const bool& Pong::Ball::CheckForLeftPaddleCollision(const Pong::Paddle& leftPaddle)
{
	// Check the collisions between the mainBall and the paddles
	// Left Paddle
	if (mainBall.getPosition().x < leftPaddle.GetMainPaddleRef().getPosition().x + leftPaddle.GetPaddleSize().x / 2 &&
		mainBall.getPosition().x - ballRadius > leftPaddle.GetMainPaddleRef().getPosition().x &&
		mainBall.getPosition().y + ballRadius >= leftPaddle.GetMainPaddleRef().getPosition().y - leftPaddle.GetPaddleSize().y / 2 &&
		mainBall.getPosition().y - ballRadius <= leftPaddle.GetMainPaddleRef().getPosition().y + leftPaddle.GetPaddleSize().y / 2)
	{
		if (mainBall.getPosition().y > leftPaddle.GetMainPaddleRef().getPosition().y)
			ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
		else
			ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

		//ballSound.play();
		mainBall.setPosition(leftPaddle.GetMainPaddleRef().getPosition().x + ballRadius + leftPaddle.GetPaddleSize().x / 2 + 0.1f, mainBall.getPosition().y);
		return true;
	}

	return false;
}

const bool& Pong::Ball::CheckForRightPaddleCollision(const Pong::Paddle& rightPaddle)
{
	// Right Paddle
	if (mainBall.getPosition().x + ballRadius > rightPaddle.GetMainPaddleRef().getPosition().x - rightPaddle.GetPaddleSize().x / 2 &&
		mainBall.getPosition().x + ballRadius < rightPaddle.GetMainPaddleRef().getPosition().x &&
		mainBall.getPosition().y + ballRadius >= rightPaddle.GetMainPaddleRef().getPosition().y - rightPaddle.GetPaddleSize().y / 2 &&
		mainBall.getPosition().y - ballRadius <= rightPaddle.GetMainPaddleRef().getPosition().y + rightPaddle.GetPaddleSize().y / 2)
	{
		if (mainBall.getPosition().y > rightPaddle.GetMainPaddleRef().getPosition().y)
			ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
		else
			ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;

		//ballSound.play();
		mainBall.setPosition(rightPaddle.GetMainPaddleRef().getPosition().x - ballRadius - rightPaddle.GetPaddleSize().x / 2 - 0.1f, mainBall.getPosition().y);
		return true;
	}

	return false;
}

void Pong::Ball::UpdateAIPaddleMovement(Pong::Paddle& rightPaddle, const float& deltaTime)
{
	if (((rightPaddle.GetSpeed() < 0.f) && (rightPaddle.GetMainPaddleRef().getPosition().y - rightPaddle.GetPaddleSize().y / 2 > 5.f)) ||
		((rightPaddle.GetSpeed() > 0.f) && (rightPaddle.GetMainPaddleRef().getPosition().y + rightPaddle.GetPaddleSize().y / 2 < Pong::SCREEN_HEIGHT - 5.f)))
	{
		rightPaddle.MoveAIPaddle(deltaTime);
	}

	if (rightPaddle.GetAITimerRef().getElapsedTime() > rightPaddle.GetMaxHitTime())
	{
		rightPaddle.GetAITimerRef().restart();
		if (mainBall.getPosition().y + ballRadius > rightPaddle.GetMainPaddleRef().getPosition().y + rightPaddle.GetPaddleSize().y / 2)
			rightPaddle.UpdateAIPaddleSpeed(1);
		else if (mainBall.getPosition().y - ballRadius < rightPaddle.GetMainPaddleRef().getPosition().y - rightPaddle.GetPaddleSize().y / 2)
			rightPaddle.UpdateAIPaddleSpeed(-1);
		else
			rightPaddle.UpdateAIPaddleSpeed(0);
	}
}