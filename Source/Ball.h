#ifndef BALL_H
#define BALL_H

#include "Common.h"
#include "Paddle.h"

namespace Pong
{
	class Ball : Pong::Common
	{
	public:
		void Init(const float& width, const float& height);
		void Update(const sf::VideoMode& videoMode, const float& deltaTime);
		bool CheckForLeft_BoundryCollision();
		bool CheckForRight_BoundryCollision(const float& screenWidth);
		void CheckForLeftPaddleCollision(const Pong::Paddle& leftPaddle);
		void CheckForRightPaddleCollision(const Pong::Paddle& rightPaddle);
		sf::CircleShape mainCircleShape;
	private:
		//Used for determining ball's move direction(based on angle)
		float ballAngle = 0.0f;
		float ballRadius;

		const float pi = 3.14159f;
	};
}
#endif