#ifndef COMMONELEMENTSHANDLER_H
#define COMMONELEMENTSHANDLER_H

#include "BaseAppClass.h"
#include "TextHandler.h"
#include <SFML/Audio.hpp>

namespace Pong
{
	/// <summary>
	/// Common class for text/bg-image rendering and also contains main menu elements
	/// </summary>
	class CommonElementsHandler : Pong::BaseAppClass
	{
	public:
		virtual ~CommonElementsHandler() = default;
		//Returns true if initialization is successful
		bool Init(sf::RenderWindow& mainRenderWindow);
		void PlayBallAudio();

		sf::Text& GetMainTextRef();

		void Render(sf::RenderWindow& mainRenderWindow) override;

		TextHandler startgame_Text;
		TextHandler quitgame_Text;
		//P v P or P v C(Against AI)
		TextHandler playmode;
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