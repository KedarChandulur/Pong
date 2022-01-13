#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

namespace Pong
{
	//Variables are in Caps just for visual representation/differentiation
	extern const unsigned short SCREEN_WIDTH;
	extern const unsigned short SCREEN_HEIGHT;

	//Global bool for checking if the game is running or in not(in menu)
	extern bool inGame;
}

namespace Pong
{
	/// <summary>
	/// Common namespace for Global enum
	/// </summary>
	namespace GlobalEnums
	{
		//Each level/difficulty updates the paddle's speed by removing the enum value amount
		enum DifficultyLevel : unsigned short
		{
			VeryHigh = 45,
			High = 100,
			Medium = 155,
			Low = 210,
		};
	}
}
#endif