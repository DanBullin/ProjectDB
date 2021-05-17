#include "GameObjects/Objects/StaticImage.h"

/*! \file StaticImage.cpp
* \brief CPP file for StaticImage
*
* Implementation for StaticImage
*
*/

/*!
\param pos a const sf::Vector2f - The position of the object
\param size a const sf::Vector2f - The size of the object
\param scale a const sf::Vector2f - The scale of the object
\param textureName a const std::string - The texture name
*/
StaticImage::StaticImage(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f scale, const std::string textureName)
{
	m_name = "Static Image";
	m_enabled = false;
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(pos);
	rec->setSize(size);
	rec->scale(scale);
	rec->setTexture(ResourceManager::getInstance()->getTexture(textureName));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool StaticImage::contains(const sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void StaticImage::update(Game* game)
{
	
}