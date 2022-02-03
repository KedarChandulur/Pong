#ifndef BALL_H
#define BALL_H

#include "Paddle.h"
#include "CommonElementsHandler.h"

namespace Pong
{
	class Paddle;

	/// <summary>
	/// Creates and controls Main Ball
	/// </summary>
	class Ball : private Pong::BaseAppClass
	{
	public:
		Ball() = default;
		virtual ~Ball() = default;

		void Init();
		void SetRandomAngle();

		//void UpdateAIPaddleMovement(Pong::Paddle& rightPaddle, const float& deltaTime);

		void CheckForTopAndBottom_BoundryCollision(const float& deltaTime);

		void CheckForLeftPaddleCollision(const Pong::Paddle& leftPaddle, Pong::CommonElementsHandler& commonElementsHandler);
		void CheckForRightPaddleCollision(const Pong::Paddle& rightPaddle, Pong::CommonElementsHandler& commonElementsHandler);

		bool CheckForLeft_BoundryCollision() const;
		bool CheckForRight_BoundryCollision() const;

		void Render(sf::RenderWindow& mainRenderWindow) override;

		const sf::CircleShape& GetMainBall() const;
		const float& GetRadius() const;
	private:
		sf::CircleShape mainBall;

		float speed = 225.0f;
		//Used for determining ball's move direction(based on angle)
		float ballAngle = 0.0f;
		float ballRadius = 5.0f;

		const float pi = 3.14159f;
		const uint16_t outLineThickness = 3;
	};
}
#endif