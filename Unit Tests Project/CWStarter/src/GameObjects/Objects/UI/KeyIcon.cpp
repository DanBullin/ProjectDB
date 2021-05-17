#include "GameObjects/Objects/UI/KeyIcon.h"

/*! \file KeyIcon.cpp
* \brief CPP file for KeyIcon
*
* Implementation for KeyIcon
*
*/

//! Constructor()
KeyIcon::KeyIcon()
{
	// Create properties
	m_name = "KeyIcon";
	m_updatedTexture = false;
	// Create SFML Rectangle
	sf::RectangleShape* rec = new sf::RectangleShape;
	// Pos is updated auto so just set it to 0,0
	rec->setPosition(0.f, 0.f);
	rec->setSize(sf::Vector2f(0.32f, 0.32f));
	rec->setTexture(ResourceManager::getInstance()->getTexture("nokey"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool KeyIcon::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void KeyIcon::update(Game* game)
{
	// If the texture hasnt been updated
	if (!m_updatedTexture)
	{
		// Get the player
		Player* player = static_cast<Player*>(game->getObject("Player"));
		if (player == nullptr) { return; }

		// If the player has collected the key, update sprite
		if (player->getKeyCollected())
		{
			// Set sprite to the key texture
			sf::RectangleShape* keytmp = static_cast<sf::RectangleShape*>(m_drawable);
			keytmp->setTexture(ResourceManager::getInstance()->getTexture("key"));
			// Set to true to stop this player conversion + sprite update from processing
			m_updatedTexture= true;
		}
	}
}