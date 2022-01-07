#ifndef BALL_H
#define BALL_H

#include "Paddle.h"

namespace Pong
{
	class Ball : protected Pong::Common
	{
	public:
		void Init();
		void SetRandomAngle();

		void CheckForTopAndBottom_BoundryCollision(const float& deltaTime);
		void CheckForLeftPaddleCollision(const Pong::Paddle& leftPaddle);
		void CheckForRightPaddleCollision(const Pong::Paddle& rightPaddle);

		const bool CheckForLeft_BoundryCollision() const;
		const bool CheckForRight_BoundryCollision() const;

		const sf::CircleShape& GetMainBallRef() const;
	private:
		sf::CircleShape mainBall;

		//Used for determining ball's move direction(based on angle)
		float ballAngle = 0.0f;
		float ballRadius;

		const float pi = 3.14159f;
	};
}
#endif