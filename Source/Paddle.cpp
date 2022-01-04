#include "Paddle.h"

void Pong::Paddle::Init(const sf::Color& paddleColor, const float& paddleoffset)
{
	//this->mainPaddle.setSize(this->paddleSize);
	this->mainPaddle.setSize(this->paddleSize - sf::Vector2f(outLineThickness, outLineThickness));

	this->mainPaddle.setOutlineThickness(this->outLineThickness);
	this->mainPaddle.setOutlineColor(paddleColor);
	this->mainPaddle.setOrigin(paddleSize/2.0f);
	this->mainPaddle.setPosition(Pong::SCREEN_WIDTH * paddleoffset, Pong::SCREEN_HEIGHT / 2.f - (paddleSize.x * 2));

	this->speed = 1000.0f;
}

void Pong::Paddle::MoveUp(const float& deltaTime)
{
	if (this->mainPaddle.getPosition().y - paddleSize.y / 2 > 5.0f)
	{
		this->mainPaddle.move(0.f, -this->speed * deltaTime);
	}
}

void Pong::Paddle::MoveDown(const float& deltaTime)
{
	if (this->mainPaddle.getPosition().y + paddleSize.y / 2 < Pong::SCREEN_HEIGHT - 5.0f)
	{
		this->mainPaddle.move(0.f, this->speed * deltaTime);
	}
}

const sf::RectangleShape& Pong::Paddle::GetMainPaddleRef() const
{
	return mainPaddle;
}