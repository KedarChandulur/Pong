#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <SFML/Graphics.hpp>

namespace Pong
{
	struct TextHandler
	{
	public:
		void SetIsSelected(const bool& isSelected);

		sf::Text& GetTextRef();

		const bool& GetIsSelected() const;
		static const unsigned short textSize = 30;
	private:
		sf::Text text_Ref;
		bool isSelected = false;
	};
}
#endif