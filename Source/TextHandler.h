#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <SFML/Graphics.hpp>

namespace Pong
{
	/// <summary>
	/// Base Text Handler struct.
	/// </summary>
	struct TextHandler
	{
	public:
		void SetIsSelected(bool isSelected);

		sf::Text& GetTextRef();

		const bool& GetIsSelected() const;

		static const uint16_t textSize = 30;
	private:
		sf::Text text_Ref;
		bool isSelected = false;
	};
}
#endif