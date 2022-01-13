#include "GlobalVariables.h"

namespace Pong
{
	const uint16_t SCREEN_WIDTH = 1280;
	//Adjusting height based on screen width and (required) aspect ratio
	const uint16_t SCREEN_HEIGHT = SCREEN_WIDTH / 16 * 9;

	bool inGame = false;
}