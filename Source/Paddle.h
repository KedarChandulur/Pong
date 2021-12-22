#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

namespace Pong
{
	class Paddle
	{
	public:
		void Init(const float& paddleSpeed, const sf::Color& paddleColor, const sf::VideoMode& videoMode, const float& paddleoffset);
		sf::RectangleShape mainPaddleShape;
	private:
		float paddleSpeed = 0.0f;
		const float outLineThickness = 2.5f;
		const sf::Vector2f paddleSize{ 25.0f, 100.0f };
	};
}
#endif