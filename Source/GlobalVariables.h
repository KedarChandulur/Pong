#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

namespace Pong
{
	//Variables are in Caps just for visual representation/differentiation
	extern const unsigned short SCREEN_WIDTH;
	extern const unsigned short SCREEN_HEIGHT;

	extern bool inGame;
}

namespace Pong
{
	namespace GlobalEnums
	{
		//Each level/difficulty updates the paddle's speed by removing the level(enum value) amount
		enum DifficultyLevel : unsigned short
		{
			VeryHigh = 50,
			High = 100,
			Medium = 150,
			Low = 200,
		};
	}
}
#endif