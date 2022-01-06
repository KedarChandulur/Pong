#ifndef PADDLE_H
#define PADDLE_H

#include "Common.h"
#include <SFML/Graphics.hpp>

namespace Pong
{
	class Paddle : protected Pong::Common
	{
	public:
		void Init(const sf::Color& paddleColor, const float& paddleoffset);
		void MoveUp(const float& deltaTime);
		void MoveDown(const float& deltaTime);

		const sf::RectangleShape& GetMainPaddleRef() const;

		const sf::Vector2f paddleSize{ 25.0f, 100.0f };
	private:
		sf::RectangleShape mainPaddle;
	};
}
#endif