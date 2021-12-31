#ifndef PADDLE_H
#define PADDLE_H

#include "Common.h"
#include <SFML/Graphics.hpp>

namespace Pong
{
	class Paddle : Pong::Common
	{
	public:
		void Init(const sf::Color& paddleColor, const sf::VideoMode& videoMode, const float& paddleoffset);
		void MoveUp(const float& deltaTime);
		void MoveDown(const sf::VideoMode& videoMode, const float& deltaTime);
		sf::RectangleShape mainPaddleShape;
		const sf::Vector2f paddleSize{ 25.0f, 100.0f };
	private:
		const float outLineThickness = 2.5f;
	};
}
#endif