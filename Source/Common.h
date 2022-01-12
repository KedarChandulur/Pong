#ifndef COMMON_H
#define COMMON_H

#include "GlobalVariables.h"
#include <SFML/Graphics.hpp>

namespace Pong
{
	struct Common
	{
	public:
		Common() = default;
		//Adding virtual destructor for safety(to avoid memory leaks)
		virtual ~Common() = default;
		virtual void Render(sf::RenderWindow& mainRenderWindow) const = 0;
	protected:
		float speed = 225.0f;

		static const unsigned short outLineThickness = 3;
	};
}
#endif