#include "Paddle.h"

void Pong::Paddle::Init(const float& paddleSpeed, const sf::Color& paddleColor, const sf::VideoMode& videoMode, const float& paddleoffset)
{
	this->mainPaddleShape.setSize(this->paddleSize - sf::Vector2f(outLineThickness, outLineThickness));
	this->mainPaddleShape.setOutlineThickness(this->outLineThickness);
	this->mainPaddleShape.setOutlineColor(paddleColor);
	this->mainPaddleShape.setPosition(videoMode.width * paddleoffset, videoMode.height / 2.f - (paddleSize.x * 2));

	this->paddleSpeed = paddleSpeed;
}