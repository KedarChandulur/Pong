#ifndef PADDLE_H
#define PADDLE_H

#include "Common.h"

namespace Pong
{
	/// <summary>
	/// Creates and controls Paddle(s)
	/// </summary>
	class Paddle : protected Pong::Common
	{
	public:
		Paddle() = default;
		~Paddle() = default;

		void Init(bool isFirstPaddle);
		void MoveUp(const float& deltaTime);
		void MoveDown(const float& deltaTime);

		//Used for reseting or re-initializing speed variable
		void ValidateManualSpeed();
		//Sets speed variable to default value
		void ResetSpeed();
		void UpdateAIPaddleSpeed(const int16_t updatedSpeed);
		void MoveAIPaddle(const float& deltaTime);

		Pong::GlobalEnums::DifficultyLevel& GetDifficultyVariableRef();

		sf::Clock& GetAITimerRef() const;

		const sf::Time& GetMaxHitTime() const;
		const sf::RectangleShape& GetMainPaddleRef() const;
		const sf::Vector2f& GetPaddleSize() const;
		const float& GetSpeed() const;
		
		void Render(sf::RenderWindow& mainRenderWindow) const override;

		static bool playAgainstAI;
	private:
		sf::RectangleShape mainPaddle;

		Pong::GlobalEnums::DifficultyLevel difficultyLevel = Pong::GlobalEnums::DifficultyLevel::Medium;

		static sf::Vector2f paddleSize;
		static sf::Clock AI_Timer;
		static sf::Time max_AI_hitTime;

		static const uint16_t defaultSpeed = 1000U;
	};
}
#endif