#include "CommonElementsHandler.h"
#include "GlobalVariables.h"

bool Pong::CommonElementsHandler::Init(sf::RenderWindow& mainRenderWindow)
{
	if (!iconImage_Ref.loadFromFile("Resources/pong_icon.png"))
		printf("%s", "Error loading the Icon Image.\n");

	printf("%s", "Icon Image loaded.\n");
	mainRenderWindow.setIcon(iconImage_Ref.getSize().x, iconImage_Ref.getSize().y, iconImage_Ref.getPixelsPtr());

	if (!fontRef.loadFromFile("Resources/Pacifico-Regular.ttf"))
	{
		printf("%s", "Error loading the Font.\n");
		return false;
	}

	printf("%s", "Font loaded.\n");
	
	if (!ballSB.loadFromFile("Resources/mixkit-game-ball-tap-2073.wav"))
	{
		return false;
	}

	bgTexture.create(Pong::SCREEN_WIDTH, Pong::SCREEN_HEIGHT);

	if (!bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{
		printf("%s", "Error loading the background texture.\n");
		return false;
	}

	printf("%s", "Background texture loaded successfully.\n");
	bgSprite.setTexture(bgTexture);
	UpdateBGSpriteScaleBasedOnRes();

	title_Text.GetTextRef().setFont(fontRef);
	startgame_Text.GetTextRef().setFont(fontRef);
	quitgame_Text.GetTextRef().setFont(fontRef);

	//title_Text.GetTextRef().setString("Hello, Welcome to Pong\nPress Space to play.\nSet the AI Level using the keys below\n1(Min) - 4(Max)");
	//title_Text.GetTextRef().setString("Hello, Welcome to Pong\nPress Space to play.");
	title_Text.GetTextRef().setString("Hello, Welcome to Pong");
	startgame_Text.GetTextRef().setString("Start");
	quitgame_Text.GetTextRef().setString("Quit");

	title_Text.GetTextRef().setOrigin(title_Text.GetTextRef().getLocalBounds().width / 2, title_Text.GetTextRef().getLocalBounds().height / 2);
	startgame_Text.GetTextRef().setOrigin(startgame_Text.GetTextRef().getLocalBounds().width / 2, startgame_Text.GetTextRef().getLocalBounds().height / 2);
	quitgame_Text.GetTextRef().setOrigin(quitgame_Text.GetTextRef().getLocalBounds().width / 2, quitgame_Text.GetTextRef().getLocalBounds().height / 2);

	title_Text.GetTextRef().setCharacterSize(Pong::TextHandler::textSize * 2);
	//startgame_Text.GetTextRef().setCharacterSize(textSize);
	//quitgame_Text.GetTextRef().setCharacterSize(textSize);

	title_Text.GetTextRef().setFillColor(sf::Color(128U, 128U, 128U));
	//startgame_Text.GetTextRef().setFillColor(sf::Color::Green);
	startgame_Text.SetIsSelected(true);
	//quitgame_Text.GetTextRef().setFillColor(sf::Color::Red);
	quitgame_Text.SetIsSelected(false);

	title_Text.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f - Pong::TextHandler::textSize * 4, Pong::TextHandler::textSize * 4);
	startgame_Text.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f, Pong::SCREEN_HEIGHT / 2.0f + 25.0f);
	quitgame_Text.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f, Pong::SCREEN_HEIGHT / 2.0f + (Pong::TextHandler::textSize * 2 + 25.0f));

	ballBounceSound.setBuffer(ballSB);
	ballBounceSound.setVolume(50.0f);

	return true;
}

void Pong::CommonElementsHandler::UpdateBGSpriteScaleBasedOnRes()
{
	bgSprite.setScale(
		Pong::SCREEN_WIDTH / bgSprite.getLocalBounds().width,
		Pong::SCREEN_HEIGHT / bgSprite.getLocalBounds().height);
}

void Pong::CommonElementsHandler::Render(sf::RenderWindow& mainRenderWindow)
{
	if (!Pong::inGame)
	{
		mainRenderWindow.draw(title_Text.GetTextRef());
		mainRenderWindow.draw(startgame_Text.GetTextRef());
		mainRenderWindow.draw(quitgame_Text.GetTextRef());
	}
	else
	{
		mainRenderWindow.draw(bgSprite);
	}
}

sf::Sound& Pong::CommonElementsHandler::GetSoundObject()
{
	return ballBounceSound;
}

sf::Text& Pong::CommonElementsHandler::GetMainTextRef()
{
	return title_Text.GetTextRef();
}

//sf::Text& Pong::CommonElementsHandler::GetStartGameTextRef()
//{
//	return startgame_Text.GetTextRef();
//}
//
//sf::Text& Pong::CommonElementsHandler::GetQuitGameTextRef()
//{
//	return quitgame_Text.GetTextRef();
//}