#ifndef COMMONELEMENTSHANDLER_H
#define COMMONELEMENTSHANDLER_H

#include "GlobalVariables.h"
#include <SFML/Graphics.hpp>

namespace Pong
{
	class CommonElementsHandler
	{
	public:
		//Returns true if initialization is successfull
		bool Init(sf::RenderWindow& mainRenderWindow);
		void UpdateBGSpriteScaleBasedOnRes();

		const sf::Sprite& GetBGSpriteRef() const;
		sf::Text& GetMainTextRef();
	private:

		//Background Sprite
		sf::Sprite bgSprite;
		/*sf::RectangleShape bgSprite;*/
		//Background Texture
		sf::Texture bgTexture;
		//Icon and main menu image
		sf::Image iconImage_Ref;
		//Custom Font
		sf::Font fontRef;
		//Main Text Ref
		sf::Text textRef;

		const char textSize = 80;
	};
}
#endif