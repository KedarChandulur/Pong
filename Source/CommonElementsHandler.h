#ifndef COMMONELEMENTSHANDLER_H
#define COMMONELEMENTSHANDLER_H

#include "GlobalVariables.h"
#include "TextHandler.h"
#include <SFML/Audio.hpp>

namespace Pong
{
	class CommonElementsHandler
	{
	public:
		//Returns true if initialization is successful
		bool Init(sf::RenderWindow& mainRenderWindow);
		void Render(sf::RenderWindow& mainRenderWindow);

		sf::Sound& GetSoundObject();
		sf::Text& GetMainTextRef();

		TextHandler startgame_Text;
		TextHandler quitgame_Text;
	private:
		//Background Sprite
		sf::Sprite bgSprite;
		//Background Texture
		sf::Texture bgTexture;
		sf::Image iconImage_Ref;

		//Custom Font Reference
		sf::Font fontRef;
		TextHandler title_Text;
		//Buffer which loads and stores audio sample of ball bounce
		sf::SoundBuffer ballSB;
		sf::Sound ballBounceSound;		
	};
}
#endif