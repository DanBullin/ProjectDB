#include "GameObjects/Objects/Physics/MovingPlatform.h"

/*! \file MovingPlatform.cpp
* \brief CPP file for MovingPlatform
*
* Implementation for MovingPlatform
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param posX a const float - The x position
\param posY a const float - The y position
\param velocity a const b2Vec2 - The movement velocity
\param maxTime a const unsigned int - The max movement time sequence
*/
MovingPlatform::MovingPlatform(b2World* world, const float posX, const float posY, const b2Vec2 velocity, const unsigned int maxTime)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "MovingPlatform";
	sf::Vector2f size(1.28f, 0.32f);
	m_velocity = velocity;
	m_currentTime = maxTime / 2;
	m_maxTime = maxTime;

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_kinematicBody, b2Vec2(posX, posY), 0, this);
	maker.addFixture(m_body, 0.5f, 0.01f, 0.1f, false, &maker.createPolygonShape(b2Vec2(size.x, size.y)));
	m_body->SetLinearVelocity(m_velocity);

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(posX, posY);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setTextureRect(sf::IntRect(0, 0, 128, 30));
	rec->setTexture(ResourceManager::getInstance()->getTexture("platform"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool MovingPlatform::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void MovingPlatform::update(Game* game)
{
	// Increase time
	m_currentTime++;
	if (m_currentTime > m_maxTime)
	{
		// If the max time has been reached
		// Inverse velocity and reset time
		m_velocity = -m_velocity;
		m_body->SetLinearVelocity(m_velocity);
		m_currentTime = 0;
	}
	// Update position
	b2Vec2 pos = m_body->GetPosition();
	static_cast<sf::RectangleShape*>(m_drawable)->setPosition(pos.x, pos.y);
}