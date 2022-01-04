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
	
	static const unsigned int SCREEN_WIDTH = 800;
	static const unsigned int SCREEN_HEIGHT = 600;
}
#endif