#include "GameObjects/Objects/UI/DynamicText.h"

/*! \file DynamicText.cpp
* \brief CPP file for DynamicText
*
* Implementation for DynamicText
*
*/

/*!
\param text a const std::string - The text contents to display
\param pos a const sf::Vector2f - The position of the object
\param characterSize a const unsigned int - The character size of the text
\param releaseAction a const unsigned int - The action index (1-4)
*/
DynamicText::DynamicText(const std::string text, const sf::Vector2f pos, const unsigned int characterSize, const unsigned int releaseAction)
{
	m_name = "DynamicText";
	m_releaseAction = releaseAction;
	m_enabled = false;

	sf::Text* textShape = new sf::Text;
	textShape->setPosition(pos);
	textShape->setCharacterSize(characterSize);
	textShape->setFillColor(sf::Color::White);
	textShape->setString(text);
	textShape->scale(0.01f, 0.01f);
	textShape->setFont(*ResourceManager::getInstance()->getFont("arial"));
	m_drawable = textShape;
	EventListener::getInstance()->attach(this);
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool DynamicText::contains(sf::Vector2f pos)
{
	// If shape contains the mouse, return true
	if (static_cast<sf::Text*>(m_drawable)->getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void DynamicText::update(Game* game)
{

}

/*!
\param game a Game* - A pointer to the game
*/
void DynamicText::mouseEnter(Game * game)
{
	// Increase size and change colour
	sf::Text* tmp = static_cast<sf::Text*>(m_drawable);
	tmp->setFillColor(sf::Color::Yellow);
	tmp->setCharacterSize(tmp->getCharacterSize() + 10);
}

/*!
\param game a Game* - A pointer to the game
*/
void DynamicText::mouseLeave(Game * game)
{
	// Reduce size and change colour
	sf::Text* tmp = static_cast<sf::Text*>(m_drawable);
	tmp->setFillColor(sf::Color::White);
	tmp->setCharacterSize(tmp->getCharacterSize() - 10);
}

/*!
\param game a Game* - A pointer to the game
*/
void DynamicText::mouseRelease(Game * game)
{
	// Check what the release action is
	switch (m_releaseAction)
	{
		case 1:
			game->showScene("Level", true);
			break;
		case 2:
			game->showScene("Pause", false);
			break;
		case 3:
			game->getScene("Level")->scheduleForDeletion(true);
			game->showScene("MainMenu", true);
			break;
		case 4:
			game->getWindow()->close();
			break;
		default:
			break;
	}
}