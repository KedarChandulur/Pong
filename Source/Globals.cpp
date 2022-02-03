#include "Globals.h"

namespace Pong
{
	const uint16_t GlobalVariables::SCREEN_WIDTH = 1280;
	//Adjusting height based on screen width and (required) aspect ratio
	const uint16_t GlobalVariables::SCREEN_HEIGHT = GlobalVariables::SCREEN_WIDTH / 16 * 9;

	bool GlobalVariables::inGame = false;
}