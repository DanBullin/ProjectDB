#include "GameObjects/Objects/Physics/Box.h"

/*! \file Box.cpp
* \brief CPP file for Box
*
* Implementation for Box
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param position a const sf::Vector2f& - The position of the box
\param size a const sf::Vector2f& - The size of the box
*/
Box::Box(b2World* world, const sf::Vector2f & position, const sf::Vector2f & size)
	: PhysicsObject(world)
{
	m_name = "Box";

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_dynamicBody, b2Vec2(position.x, position.y), 0, this);
	maker.addFixture(m_body, 0.5f, 1.f, 0.3f, false, &maker.createPolygonShape(b2Vec2(size.x, size.y)));

	// Create SFML properties
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setRotation(0);
	rec->setTextureRect(sf::IntRect(0, 0, 32, 32));
	rec->setTexture(ResourceManager::getInstance()->getTexture("box"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool Box::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void Box::update(Game* game)
{
	// Set the SFML's shape position and angle based on body's
	b2Vec2 pos = m_body->GetPosition();
	static_cast<sf::RectangleShape*>(m_drawable)->setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	static_cast<sf::RectangleShape*>(m_drawable)->setRotation(angle);
}
