#include "CommonElementsHandler.h"
#include "Log.h"

//Returning false only for font loading because with all other elements not loaded the game is still playable with some elements/effects missing.
//But without font, game's menu text itself is not visible - so returning false only on font failure.
bool Pong::CommonElementsHandler::Init(sf::RenderWindow& mainRenderWindow)
{
	if (!fontRef.loadFromFile("Resources/Pacifico-Regular.ttf"))
	{
		Pong::Log::Print("Error loading the Font.");
		return false;
	}
	else
	{
		Pong::Log::Print("Font loaded.");
	}

	if (!iconImage_Ref.loadFromFile("Resources/pong_icon.png"))
	{
		Pong::Log::Print("Error loading the Icon Image.");
	}
	else
	{
		Pong::Log::Print("Icon Image loaded.");
		mainRenderWindow.setIcon(iconImage_Ref.getSize().x, iconImage_Ref.getSize().y, iconImage_Ref.getPixelsPtr());
	}
	
	if (!ballSB.loadFromFile("Resources/mixkit-game-ball-tap-2073.wav"))
	{
		Pong::Log::Print("Error loading the Audio clip.");
	}
	else
	{
		Pong::Log::Print("Audio clip loaded.");
	}

	if (!bgTexture.loadFromFile("Resources/Pong_BG.png"))
	{
		Pong::Log::Print("Error loading the background texture.");

		sf::Image tempImage = sf::Image();
		tempImage.create(Pong::SCREEN_WIDTH, Pong::SCREEN_HEIGHT, sf::Color::Blue);		
		bgTexture.loadFromImage(tempImage);
	}
	else
	{
		Pong::Log::Print("Background texture loaded successfully.");
	}

	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(
		Pong::SCREEN_WIDTH / bgSprite.getLocalBounds().width,
		Pong::SCREEN_HEIGHT / bgSprite.getLocalBounds().height);

	title_Text.GetTextRef().setFont(fontRef);
	startgame_Text.GetTextRef().setFont(fontRef);
	quitgame_Text.GetTextRef().setFont(fontRef);
	playmode.GetTextRef().setFont(fontRef);

	title_Text.GetTextRef().setString("Hello, Welcome to Pong");
	startgame_Text.GetTextRef().setString("Start");
	quitgame_Text.GetTextRef().setString("Quit");
	playmode.GetTextRef().setString("P v C");

	title_Text.GetTextRef().setOrigin(title_Text.GetTextRef().getLocalBounds().width / 2, title_Text.GetTextRef().getLocalBounds().height / 2);
	startgame_Text.GetTextRef().setOrigin(startgame_Text.GetTextRef().getLocalBounds().width / 2, startgame_Text.GetTextRef().getLocalBounds().height / 2);
	quitgame_Text.GetTextRef().setOrigin(quitgame_Text.GetTextRef().getLocalBounds().width / 2, quitgame_Text.GetTextRef().getLocalBounds().height / 2);
	playmode.GetTextRef().setOrigin(playmode.GetTextRef().getLocalBounds().width / 2, playmode.GetTextRef().getLocalBounds().height / 2);

	title_Text.GetTextRef().setCharacterSize(Pong::TextHandler::textSize * 2);
	playmode.GetTextRef().setCharacterSize(Pong::TextHandler::textSize + 15U);

	title_Text.GetTextRef().setFillColor(sf::Color(128U, 128U, 128U));
	startgame_Text.SetIsSelected(true);
	quitgame_Text.SetIsSelected(false);
	playmode.GetTextRef().setFillColor(sf::Color(128U, 128U, 128U));

	title_Text.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f - Pong::TextHandler::textSize * 4, Pong::TextHandler::textSize * 4);
	startgame_Text.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f, Pong::SCREEN_HEIGHT / 2.0f + 50.0f);
	quitgame_Text.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f, Pong::SCREEN_HEIGHT / 2.0f + (Pong::TextHandler::textSize * 2 + 50.0f));
	playmode.GetTextRef().setPosition(Pong::SCREEN_WIDTH / 2.0f, Pong::SCREEN_HEIGHT / 2.0f + Pong::TextHandler::textSize * 10);

	ballBounceSound.setBuffer(ballSB);
	ballBounceSound.setVolume(30.0f);

	return true;
}

void Pong::CommonElementsHandler::Render(sf::RenderWindow& mainRenderWindow)
{
	if (!Pong::inGame)
	{
		mainRenderWindow.draw(title_Text.GetTextRef());
		mainRenderWindow.draw(startgame_Text.GetTextRef());
		mainRenderWindow.draw(quitgame_Text.GetTextRef());
		mainRenderWindow.draw(playmode.GetTextRef());
	}
	else
	{
		mainRenderWindow.draw(bgSprite);
	}
}

sf::Text& Pong::CommonElementsHandler::GetMainTextRef()
{
	return title_Text.GetTextRef();
}

void Pong::CommonElementsHandler::PlayBallAudio()
{
	if (ballBounceSound.getStatus() == sf::SoundSource::Status::Playing)
		ballBounceSound.stop();
	ballBounceSound.play();
}