#ifndef PADDLE_H
#define PADDLE_H

#include "Common.h"

namespace Pong
{
	class Paddle : protected Pong::Common
	{
	public:
		Paddle() = default;
		~Paddle() = default;

		void Init(bool isFirstPaddle);
		void MoveUp(const float& deltaTime);
		void MoveDown(const float& deltaTime);
		void UpdateAIPaddleSpeedEnum(const Pong::GlobalEnums::DifficultyLevel& difficultyType);
		//Used for reseting or re-initializing speed variable
		void ValidateManualSpeed();
		//Sets speed variable to default value
		void ResetSpeed();

		sf::Clock& GetAITimerRef();
		const sf::Time& GetMaxHitTime();

		const void UpdateAIPaddleSpeed(const short& updatedSpeed);
		const void MoveAIPaddle(const float& deltaTime);

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

		static const unsigned short defaultSpeed = 1000U;
	};
}
#endif