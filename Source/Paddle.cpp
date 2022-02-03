#include "Paddle.h"
#include "Math.h"

void Pong::Paddle::Init(bool isFirstPaddle)
{
	mainPaddle.setSize(paddleSize - sf::Vector2f(outLineThickness, outLineThickness));

	mainPaddle.setOutlineThickness(outLineThickness);
	mainPaddle.setOrigin(paddleSize / 2.0f);

	if (isFirstPaddle)
		mainPaddle.setOutlineColor(sf::Color::Green);
	else
		mainPaddle.setOutlineColor(sf::Color::Magenta);

	if (isFirstPaddle)
		mainPaddle.setPosition(56.0f, Pong::GlobalVariables::SCREEN_HEIGHT / 2.0f - 50.0f);
	else
		mainPaddle.setPosition(Pong::GlobalVariables::SCREEN_WIDTH - 51.5f, Pong::GlobalVariables::SCREEN_HEIGHT / 2.0f - 50.0f);

	if (isFirstPaddle || !playAgainstAI)
		ValidateManualSpeed();
	else
		ResetSpeed();
}

void Pong::Paddle::ResetSpeed()
{
	speed = defaultSpeed;
}

void Pong::Paddle::ValidateManualSpeed()
{
	ResetSpeed();
	speed += static_cast<uint16_t>(Pong::GlobalEnums::DifficultyLevel::Low);
}

void Pong::Paddle::MoveUp(const float& deltaTime)
{
	if (mainPaddle.getPosition().y - paddleSize.y / 2 > 5.0f)
	{
		mainPaddle.move(0.f, -speed * deltaTime);
	}
}

void Pong::Paddle::MoveDown(const float& deltaTime)
{
	if (mainPaddle.getPosition().y + paddleSize.y / 2 < Pong::GlobalVariables::SCREEN_HEIGHT - 5.0f)
	{
		mainPaddle.move(0.f, speed * deltaTime);
	}
}

void Pong::Paddle::SetAIDifficulty(const uint16_t& difficultyLevel)
{
	this->difficultyLevel = difficultyLevel;
}

void Pong::Paddle::MoveAIPaddle(const float& deltaTime)
{
	//Using this to get random position 
	float RandomLerpValue = Pong::Math::Lerp(0.21f, 0.36f, (rand() % 10) * 0.1f);
	float targetLerpValue = mainPaddle.getPosition().y + speed * deltaTime;
	float updatedPositionWithLerp = Pong::Math::Lerp_ThroughReference(mainPaddle.getPosition().y, targetLerpValue, RandomLerpValue);

	mainPaddle.setPosition(mainPaddle.getPosition().x, updatedPositionWithLerp);
}

void Pong::Paddle::UpdateAIPaddleMovement(Pong::Ball& ball, const float& deltaTime)
{
	if (((speed < 0.f) && (mainPaddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
		((speed > 0.f) && (mainPaddle.getPosition().y + paddleSize.y / 2 < Pong::GlobalVariables::SCREEN_HEIGHT - 5.f)))
	{
		MoveAIPaddle(deltaTime);
	}

	if (AI_Timer.getElapsedTime() > max_AI_hitTime)
	{
		AI_Timer.restart();
		if (ball.GetMainBall().getPosition().y + ball.GetRadius() > mainPaddle.getPosition().y + paddleSize.y / 2)
			UpdateAIPaddleSpeed(1);
		else if (ball.GetMainBall().getPosition().y - ball.GetRadius() < mainPaddle.getPosition().y - paddleSize.y / 2)
			UpdateAIPaddleSpeed(-1);
		else
			UpdateAIPaddleSpeed(0);
	}
}

void Pong::Paddle::UpdateAIPaddleSpeed(const int16_t updatedSpeed)
{	
	speed = static_cast<float>((defaultSpeed / 2 - static_cast<uint16_t>(difficultyLevel)) * updatedSpeed);
}

void Pong::Paddle::Render(sf::RenderWindow& mainRenderWindow)
{
	mainRenderWindow.draw(mainPaddle);
}

sf::Clock& Pong::Paddle::GetAITimerRef() const
{
	return AI_Timer;
}

const sf::RectangleShape& Pong::Paddle::GetMainPaddleRef() const
{
	return mainPaddle;
}

const sf::Vector2f& Pong::Paddle::GetPaddleSize() const
{
	return paddleSize;
}

const float& Pong::Paddle::GetSpeed() const
{
	return speed;
}

const sf::Time& Pong::Paddle::GetMaxHitTime() const
{
	return max_AI_hitTime;
}

sf::Vector2f Pong::Paddle::paddleSize = sf::Vector2f(25.0f, 100.0f);
sf::Time Pong::Paddle::max_AI_hitTime = sf::seconds(0.1f);
sf::Clock Pong::Paddle::AI_Timer;
bool Pong::Paddle::playAgainstAI = true;