#include "Paddle.h"

#include <iostream>
#include <cmath>

//void Pong::Paddle::Init(const sf::Color& paddleColor, const float& paddleoffset)
//{
//	//mainPaddle.setSize(paddleSize);
//	mainPaddle.setSize(paddleSize - sf::Vector2f(outLineThickness, outLineThickness));
//
//	mainPaddle.setOutlineThickness(outLineThickness);
//	mainPaddle.setOutlineColor(paddleColor);
//	mainPaddle.setOrigin(paddleSize/2.0f);
//	mainPaddle.setPosition(Pong::SCREEN_WIDTH * paddleoffset, Pong::SCREEN_HEIGHT / 2.f - (paddleSize.x * 2));
//
//	speed = defaultSpeed;
//}

//leftPaddle_Ref.Init(sf::Color::Green, 0.05f);
//rightPaddle_Ref.Init(sf::Color::Magenta, 0.951f);
void Pong::Paddle::Init(bool isFirstPaddle)
{
	//mainPaddle.setSize(paddleSize);
	mainPaddle.setSize(paddleSize - sf::Vector2f(outLineThickness, outLineThickness));

	mainPaddle.setOutlineThickness(outLineThickness);
	mainPaddle.setOrigin(paddleSize / 2.0f);

	if (isFirstPaddle)
		mainPaddle.setOutlineColor(sf::Color::Green);
	else
		mainPaddle.setOutlineColor(sf::Color::Magenta);

	if (isFirstPaddle)
		mainPaddle.setPosition(Pong::SCREEN_WIDTH * 0.05f, Pong::SCREEN_HEIGHT / 2.f - (paddleSize.x * 2));
	else
		mainPaddle.setPosition(Pong::SCREEN_WIDTH * 0.951f, Pong::SCREEN_HEIGHT / 2.f - (paddleSize.x * 2));

	speed = defaultSpeed;

	if (isFirstPaddle || !playAgainstAI)
		ValidateManualSpeed();
	else if (playAgainstAI)
		ResetSpeed();
}

void Pong::Paddle::ResetSpeed()
{
	speed = defaultSpeed;
}

void Pong::Paddle::ValidateManualSpeed()
{
	ResetSpeed();
	speed += Pong::GlobalEnums::DifficultyLevel::Low;
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
	if (mainPaddle.getPosition().y + paddleSize.y / 2 < Pong::SCREEN_HEIGHT - 5.0f)
	{
		mainPaddle.move(0.f, speed * deltaTime);
	}
}

//void Pong::Paddle::UpdateAIPaddleSpeedEnum(const unsigned short& difficultyType)
//{
//	difficultyLevel = (Pong::GlobalEnums::DifficultyLevel)difficultyType;
//}

void Pong::Paddle::UpdateAIPaddleSpeedEnum(const Pong::GlobalEnums::DifficultyLevel& difficultyLevel)
{
	this->difficultyLevel = difficultyLevel;
}

//const void Pong::Paddle::MoveAIPaddle(const float& deltaTime)
//{
//	const float& currentPosition = mainPaddle.getPosition().y;
//	//float targetPosition = currentPosition + (speed * deltaTime);
//	const float& targetPosition = currentPosition + speed * deltaTime;
//	float randomLerpTimerValue = rand() % 10 * 0.1f;
//	//printf("%f\n", randomLerpTimerValue);
//	
//	const float& RandomLerpValue = Lerp(0.15f,0.35f, randomLerpTimerValue);
//	const float& updatedPositionWithLerp = Lerp(currentPosition, targetPosition, RandomLerpValue);
//
//	mainPaddle.setPosition(mainPaddle.getPosition().x, updatedPositionWithLerp);
//
//	//mainPaddle.move(0.f, speed * deltaTime);
//}

//const void Pong::Paddle::MoveAIPaddle(const float& deltaTime)
//{
//	mainPaddle.move(0.f, speed * deltaTime);
//}

const void Pong::Paddle::MoveAIPaddle(const float& deltaTime)
{
	const float& RandomLerpValue = Lerp(0.15f, 0.35f, rand() % 10 * 0.1f);
	const float& updatedPositionWithLerp = Lerp(mainPaddle.getPosition().y, mainPaddle.getPosition().y + speed * deltaTime, RandomLerpValue);

	mainPaddle.setPosition(mainPaddle.getPosition().x, updatedPositionWithLerp);
}
  
const void Pong::Paddle::UpdateAIPaddleSpeed(const short& updatedSpeed)
{	
	speed = static_cast<float>((defaultSpeed / 2 - difficultyLevel) * updatedSpeed);
}

void Pong::Paddle::Render(sf::RenderWindow& mainRenderWindow) const
{
	mainRenderWindow.draw(mainPaddle);
}

float Pong::Paddle::Lerp(const float& a, const float& b, const float& t)
{
	return (a * (1.0f - t)) + (b * t);
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

sf::Clock& Pong::Paddle::GetAITimerRef()
{
	return AI_Timer;
}

const sf::Time& Pong::Paddle::GetMaxHitTime()
{
	return max_AI_hitTime;
}

sf::Vector2f Pong::Paddle::paddleSize = sf::Vector2f(25.0f, 100.0f);
sf::Time Pong::Paddle::max_AI_hitTime = sf::seconds(0.1f);
sf::Clock Pong::Paddle::AI_Timer;
bool Pong::Paddle::playAgainstAI = true;