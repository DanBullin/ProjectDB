#include "GameObjects/Objects/UI/StaticText.h"

/*! \file StaticText.cpp
* \brief CPP file for StaticText
*
* Implementation for StaticText
*
*/

/*!
\param text a const std::string - The text contents to display
\param pos a const sf::Vector2f - The position of the object
\param characterSize a const unsigned int - The character size of the text
\param colour a const sf::Colour& - The colour of the text
*/
StaticText::StaticText(const std::string text, const sf::Vector2f pos, const unsigned int characterSize, const sf::Color& colour)
{
	// Name and disable its enabled as it has no update
	m_name = "StaticText";
	m_enabled = false;

	// Create text component
	sf::Text* textShape = new sf::Text;
	textShape->setPosition(pos);
	textShape->setCharacterSize(characterSize);
	textShape->setFillColor(colour);
	textShape->setString(text);
	// View is 8x6 so scale down by 100
	textShape->scale(0.01f, 0.01f);
	// Set font
	textShape->setFont(*ResourceManager::getInstance()->getFont("arial"));
	m_drawable = textShape;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool StaticText::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void StaticText::update(Game* game)
{
}