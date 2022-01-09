#include "TextHandler.h"

void Pong::TextHandler::SetIsSelected(const bool& isSelected)
{
	this->isSelected = isSelected;

	if (isSelected)
		text_Ref.setFillColor(sf::Color::Green);
	else
		text_Ref.setFillColor(sf::Color::Red);

}

sf::Text& Pong::TextHandler::GetTextRef()
{
	return text_Ref;
}

const bool& Pong::TextHandler::GetIsSelected() const
{
	return isSelected;
}