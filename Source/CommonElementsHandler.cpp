#include "CommonElementsHandler.h"

bool Pong::CommonElementsHandler::Init(sf::RenderWindow& mainRenderWindow)
{
	if (!iconImage_Ref.loadFromFile("Resources/pong_icon.png"))
		printf("Error loading the Icon Image.\n");

	printf("Icon Image loaded.\n");
	mainRenderWindow.setIcon(iconImage_Ref.getSize().x, iconImage_Ref.getSize().y, iconImage_Ref.getPixelsPtr());

	//if (!fontRef.loadFromFile("Resources/EdgeOfTheGalaxyRegular-OVEa6.otf"))
	if (!fontRef.loadFromFile("Resources/FacetsNF.ttf"))
	{
		printf("Error loading the Font.\n");
		return false;
	}

	printf("Font loaded.\n");
	textRef.setFont(fontRef);
	textRef.setString("Hello, Welcome to Pong\nPress Space to play.");
	textRef.setCharacterSize(textSize);
	//textRef.setFillColor(sf::Color::Green);
	textRef.setFillColor(sf::Color(128U,128U,128U));
	textRef.setOrigin(textSize / 2.0f, textSize / 2.0f);
	textRef.setPosition(Pong::SCREEN_WIDTH * 0.25f, Pong::SCREEN_HEIGHT * 0.40f);
	//textRef.setPosition(Pong::SCREEN_WIDTH * 0.30f, Pong::SCREEN_HEIGHT / 2);

	bgTexture.create(Pong::SCREEN_WIDTH, Pong::SCREEN_HEIGHT);

	if (!bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{
		printf("Error loading the background texture.\n");
		return false;
	}

	printf("Background texture loaded successfully.\n");
	bgSprite.setTexture(bgTexture);
	UpdateBGSpriteScaleBasedOnRes();

	return true;
}

const sf::Sprite& Pong::CommonElementsHandler::GetBGSpriteRef() const
{
	return bgSprite;
}

sf::Text& Pong::CommonElementsHandler::GetMainTextRef()
{
	return textRef;
}

void Pong::CommonElementsHandler::UpdateBGSpriteScaleBasedOnRes()
{
	bgSprite.setScale(
		Pong::SCREEN_WIDTH / bgSprite.getLocalBounds().width,
		Pong::SCREEN_HEIGHT / bgSprite.getLocalBounds().height);
}