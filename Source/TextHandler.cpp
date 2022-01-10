#include "TextHandler.h"

void Pong::TextHandler::SetIsSelected(const bool& isSelected)
{
	this->isSelected = isSelected;

	if (isSelected)
	{
		text_Ref.setFillColor(sf::Color::Green);
		text_Ref.setCharacterSize(textSize + 10);
	}
	else
	{
		text_Ref.setFillColor(sf::Color::Red);
		text_Ref.setCharacterSize(textSize);
	}
}

sf::Text& Pong::TextHandler::GetTextRef()
{
	return text_Ref;
}

const bool& Pong::TextHandler::GetIsSelected() const
{
	return isSelected;
}