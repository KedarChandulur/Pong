#ifndef PADDLE_H
#define PADDLE_H

#include "BaseAppClass.h"
#include "Ball.h"

namespace Pong
{
	class Ball;

	/// <summary>
	/// Creates and controls Paddle(s)
	/// </summary>
	class Paddle : private Pong::BaseAppClass
	{
	public:
		Paddle() = default;
		virtual ~Paddle() = default;

		void Init(bool isFirstPaddle);
		void MoveUp(const float& deltaTime);
		void MoveDown(const float& deltaTime);

		//Used for reseting or re-initializing speed variable
		void ValidateManualSpeed();
		//Sets speed variable to default value
		void ResetSpeed();

		void UpdateAIPaddleMovement(Pong::Ball& ball, const float& deltaTime);

		void UpdateAIPaddleSpeed(const int16_t updatedSpeed);

		void SetAIDifficulty(const uint16_t& difficultyLevel);

		sf::Clock& GetAITimerRef() const;

		const sf::RectangleShape& GetMainPaddleRef() const;
		const sf::Vector2f& GetPaddleSize() const;

		void Render(sf::RenderWindow& mainRenderWindow) override;

		static bool playAgainstAI;
	private:
		void MoveAIPaddle(const float& deltaTime);

		sf::RectangleShape mainPaddle;

		float speed = 225.0f;

		//Pong::GlobalEnums::DifficultyLevel difficultyLevel = Pong::GlobalEnums::DifficultyLevel::Medium;
		uint16_t difficultyLevel = static_cast<uint16_t>(Pong::GlobalEnums::DifficultyLevel::Medium);

		static sf::Vector2f paddleSize;
		static sf::Clock AI_Timer;
		static sf::Time max_AI_hitTime;

		static const uint16_t defaultSpeed = 1000U;
		static const uint16_t outLineThickness = 3;
	};
}
#endif