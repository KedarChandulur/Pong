#ifndef PADDLE_H
#define PADDLE_H

#include "Common.h"

namespace Pong
{
	//Each level/difficulty updates the paddle's speed by removing the level(enum value) amount
	/*enum AIPaddleSpeed : unsigned short
	{
		VeryHigh = 50,
		High = 100,
		Medium = 150,
		Low = 200,
	};*/

	class Paddle : protected Pong::Common
	{
	public:
		//void Init(const sf::Color& paddleColor, const float& paddleoffset);
		void Init(bool isFirstPaddle);
		void MoveUp(const float& deltaTime);
		void MoveDown(const float& deltaTime);
		//void UpdateAIPaddleSpeedEnum(const unsigned short& difficultyType);
		void UpdateAIPaddleSpeedEnum(const Pong::GlobalEnums::DifficultyLevel& difficultyType);
		//Used for reseting or re-initializing speed variable
		void ValidateManualSpeed();
		//Sets speed variable to default value
		void ResetSpeed();

		//const void UpdateAIPaddleSpeed(const short& updatedSpeed, const float& deltaTime);
		const void UpdateAIPaddleSpeed(const short& updatedSpeed);
		const void MoveAIPaddle(const float& deltaTime);

		const sf::RectangleShape& GetMainPaddleRef() const;
		const sf::Vector2f& GetPaddleSize() const;
		const float& GetSpeed() const;

		//static sf::Clock& GetAITimerRef();
		//static const sf::Time& GetMaxHitTime();
		sf::Clock& GetAITimerRef();
		const sf::Time& GetMaxHitTime();

		//const float max_AI_hitTime = 0.1f;
		//const sf::Time max_AI_hitTime = sf::seconds(0.1f);
		
		void Render(sf::RenderWindow& mainRenderWindow) const override;
		//const void OnResizeEvent() const override;

		static bool playAgainstAI;
	private:
		float Lerp(const float& a, const float& b, const float& f);

		sf::RectangleShape mainPaddle;
		Pong::GlobalEnums::DifficultyLevel difficultyLevel = Pong::GlobalEnums::DifficultyLevel::Medium;

		static sf::Vector2f paddleSize;
		static sf::Clock AI_Timer;
		static sf::Time max_AI_hitTime;

		static const unsigned short defaultSpeed = 1000U;
	};
}
#endif