#include "GameObjects/Objects/Physics/Enemy.h"

/*! \file Enemy.cpp
* \brief CPP file for Enemy
*
* Implementation for Enemy
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param posX a const float - The x position
\param posY a const float - The y position
\param velocity a const b2Vec2 - The movement velocity
\param maxTime a const unsigned int - The max movement time sequence
*/
Enemy::Enemy(b2World* world, const float posX, const float posY, const b2Vec2 velocity, const float maxTime)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "Enemy";
	m_animated = true;
	m_direction = 1;
	m_spriteSheetIndex = 0;
	sf::Vector2f size(0.48f, 0.48f);
	m_velocity = velocity; // Movement
	m_currentTime = maxTime / 2; // Enemy is in the middle so its current time needs to start at half
	m_maxTime = maxTime; // When the object changes direction

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_dynamicBody, b2Vec2(posX, posY), 0, this);
	maker.addFixture(m_body, 0.5f, 0.01f, 0.1f, false, &maker.createPolygonShape(b2Vec2(size.x, size.y)));
	m_body->SetLinearVelocity(m_velocity);

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(posX, posY);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setTextureRect(sf::IntRect(0, 18, 11, 16));
	rec->setTexture(ResourceManager::getInstance()->getTexture("enemy"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool Enemy::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void Enemy::update(Game* game)
{
	m_currentTime++;

	if (m_currentTime > m_maxTime)
	{
		// Switch direction
		m_velocity = -m_velocity;
		m_direction = !m_direction;
		m_currentTime = 0;
	}
	m_body->SetLinearVelocity(m_velocity);

	b2Vec2 pos = m_body->GetPosition();
	static_cast<sf::RectangleShape*>(m_drawable)->setPosition(pos.x, pos.y);
}

/*!
\param collider a PhysicsObject* - A pointer to the collding object
\param fixtureASensor a const bool - Is this object a sensor
\param fixtureBSensor a const bool - Is the colliding object a sensor
*/
void Enemy::enterCollision(const PhysicsObject * collider, const bool fixtureASensor, const bool fixtureBSensor)
{
	if (collider->getName() == "Player" && fixtureBSensor)
	{
		// If the player's foot collides, kill the enemy
		m_markedDeletion = true;
	}
}

//! animationUpdate()
void Enemy::animationUpdate()
{
	// Set the texture from the sprite sheet, taking into account the diring its facing and the current animation sprite
	static_cast<sf::RectangleShape*>(m_drawable)->setTextureRect(sf::IntRect(m_spriteSheetIndex * 13, m_direction * 18, 12, 17));
	// Move to the next animation sprite
	m_spriteSheetIndex++;
	// Theres only 3 animation sprites per ani so reset sprite sheet index
	if (m_spriteSheetIndex == 2) { m_spriteSheetIndex = 0; }
}