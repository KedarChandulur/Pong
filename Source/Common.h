#ifndef COMMON_H
#define COMMON_H

namespace Pong
{
	struct Common
	{
	protected:
		float speed = 150.0f;

		static const char outLineThickness = 3;
	};
	
	static const unsigned short SCREEN_WIDTH = 1280;
	static const unsigned short SCREEN_HEIGHT = 720;
}
#endif