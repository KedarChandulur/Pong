#include "Paddle.h"

void Pong::Paddle::Init(const sf::Color& paddleColor, const sf::VideoMode& videoMode, const float& paddleoffset)
{
	//this->mainPaddleShape.setSize(this->paddleSize - sf::Vector2f(outLineThickness, outLineThickness));
	this->mainPaddleShape.setSize(this->paddleSize);

	this->mainPaddleShape.setOutlineThickness(this->outLineThickness);
	this->mainPaddleShape.setOutlineColor(paddleColor);
	this->mainPaddleShape.setPosition(videoMode.width * paddleoffset, videoMode.height / 2.f - (paddleSize.x * 2));

	this->speed = 1000.0f;
}

void Pong::Paddle::MoveUp(const float& deltaTime)
{
	if (this->mainPaddleShape.getPosition().y > 6.50f)
	{
		this->mainPaddleShape.move(0.f, -speed * deltaTime);
	}
}

void Pong::Paddle::MoveDown(const sf::VideoMode& videoMode, const float& deltaTime)
{
	if (this->mainPaddleShape.getPosition().y + paddleSize.y / 2 < videoMode.height - (paddleSize.x * 2))
	{
		this->mainPaddleShape.move(0.f, speed * deltaTime);
	}
}