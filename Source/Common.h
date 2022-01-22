#ifndef COMMON_H
#define COMMON_H

#include "GlobalVariables.h"
#include <SFML/Graphics.hpp>

namespace Pong
{
	/// <summary>
	/// Common struct for Paddle and Ball variables
	/// </summary>
	struct Common
	{
	public:
		Common() = default;
		//Adding virtual destructor for safety(to avoid memory leaks)
		virtual ~Common() = default;
		virtual void Render(sf::RenderWindow& mainRenderWindow) = 0;
	protected:
		float speed = 225.0f;

		static const uint16_t outLineThickness = 3;
	};
}
#endif