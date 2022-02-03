#ifndef BASEAPPCLASS_H
#define BASEAPPCLASS_H

#include "Globals.h"
#include <SFML/Graphics.hpp>

namespace Pong
{
	/// <summary>
	/// Base App Class - Handles Common Methods required by mostly all classes.
	/// </summary>
	struct BaseAppClass
	{
		//Adding virtual destructor for safety
		virtual ~BaseAppClass() = default;
		virtual void Render(sf::RenderWindow& mainRenderWindow) = 0;
	};
}
#endif