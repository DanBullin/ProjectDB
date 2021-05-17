#include "GameObjects/Objects/Physics/Door.h"
#include "GameObjects/Objects/Physics/Player.h"

/*! \file Door.cpp
* \brief CPP file for Door
*
* Implementation for Door
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param position a const sf::Vector2f& - The position of the door
*/
Door::Door(b2World* world, const sf::Vector2f & position)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "Door";
	m_updatedTexture = false;
	sf::Vector2f size(0.64f, 0.64f);
	
	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_staticBody, b2Vec2(position.x, position.y), 0, this);
	maker.addFixture(m_body, 100.f, 0.01f, 0.3f, true, &maker.createPolygonShape(b2Vec2(size.x, size.y)));

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setTexture(ResourceManager::getInstance()->getTexture("doorlocked"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool Door::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void Door::update(Game* game)
{
	// If the texture hasn't been updated yet
	if (!m_updatedTexture)
	{
		// Check if player has collected key
		if (static_cast<Player*>(game->getObject("Player"))->getKeyCollected())
		{
			// If they have, change door texture to unlocked
			sf::RectangleShape* doortmp = static_cast<sf::RectangleShape*>(m_drawable);
			doortmp->setTexture(ResourceManager::getInstance()->getTexture("doorunlocked"));
		}
		// Texture has been updated, stop checking
		m_updatedTexture = true;
	}
}