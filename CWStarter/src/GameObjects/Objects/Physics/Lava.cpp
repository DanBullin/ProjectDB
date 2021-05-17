#include "GameObjects/Objects/Physics/Lava.h"

/*! \file Lava.cpp
* \brief CPP file for Lava
*
* Implementation for Lava
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param position a const sf::Vector2f& - The position of the lava
\param size a const sf::Vector2f& - The size of the lava
\param orientation a const float - The rotation of the lava
*/
Lava::Lava(b2World* world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "Lava";
	m_enabled = false;

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_staticBody, b2Vec2(position.x, position.y), orientation, this);
	maker.addFixture(m_body, 100.f, 0.01f, 0.3f, true, &maker.createPolygonShape(b2Vec2(size.x, size.y)));

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setRotation(orientation);
	rec->setTextureRect(sf::IntRect(0, 0, (int)(size.x * 31), 16));
	rec->setTexture(ResourceManager::getInstance()->getTexture("lava"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool Lava::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void Lava::update(Game* game)
{

}