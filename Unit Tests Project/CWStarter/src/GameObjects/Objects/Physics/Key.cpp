#include "GameObjects/Objects/Physics/Key.h"

/*! \file Key.cpp
* \brief CPP file for Key
*
* Implementation for Key
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param position a const sf::Vector2f& - The position of the key
*/
Key::Key(b2World* world, const sf::Vector2f & position)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "Key";
	m_enabled = false;
	sf::Vector2f size(0.32f, 0.32f);

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_staticBody, b2Vec2(position.x, position.y), 0, this);
	maker.addFixture(m_body, 100.f, 0.01f, 0.3f, true, &maker.createPolygonShape(b2Vec2(size.x, size.y)));

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setTexture(ResourceManager::getInstance()->getTexture("key"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool Key::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void Key::update(Game* game)
{

}

/*!
\param collider a PhysicsObject* - A pointer to the collding object
\param fixtureASensor a const bool - Is this object a sensor
\param fixtureBSensor a const bool - Is the colliding object a sensor
*/
void Key::enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor)
{
	if (collider->getName() == "Player" && !fixtureBSensor)
	{
		// If the Player's body collides, destroy this gem
		m_markedDeletion = true;
	}
}
