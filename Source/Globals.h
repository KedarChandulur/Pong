#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdint>

namespace Pong
{
	/// <summary>
	/// Common namespace for Global Variables
	/// </summary>
	namespace GlobalVariables
	{
		//Variables are in Caps just for visual representation/differentiation
		extern const uint16_t SCREEN_WIDTH;
		extern const uint16_t SCREEN_HEIGHT;

		//Global bool for checking if the game is running or in not(in menu)
		extern bool inGame;
	}

	/// <summary>
	/// Common namespace for Global enum
	/// </summary>
	namespace GlobalEnums
	{
		//Each level/difficulty updates the paddle's speed by removing the enum value amount
		enum class DifficultyLevel : uint16_t
		{
			VeryHigh = 45,
			High = 100,
			Medium = 155,
			Low = 210,
		};
	}
}
#endif