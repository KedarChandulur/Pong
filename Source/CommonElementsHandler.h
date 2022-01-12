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

		//Start Game Text Ref
		TextHandler startgame_Text;
		//Quit Game Text Ref
		TextHandler quitgame_Text;
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
		//Title Text Ref
		TextHandler title_Text;
		//Buffer which loads and stores audio file of ball bounce
		sf::SoundBuffer ballSB;
		//Sfml sound object for playing the ball bounce sound
		sf::Sound ballBounceSound;		
	};
}
#endif