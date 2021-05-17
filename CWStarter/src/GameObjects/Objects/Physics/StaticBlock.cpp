#include "GameObjects/Objects/Physics/StaticBlock.h"

/*! \file StaticBlock.cpp
* \brief CPP file for StaticBlock
*
* Implementation for StaticBlock
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param position a const sf::Vector2f& - The position of the block
\param size a const sf::Vector2f& - The size of the block
\param orientation a const float - The rotation of the block
\param textureName a const std::string - The texture name of the block
*/
StaticBlock::StaticBlock(b2World* world, const sf::Vector2f & position, const sf::Vector2f & size, const float orientation, const std::string textureName)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "StaticBlock";
	m_enabled = false;

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_staticBody, b2Vec2(position.x, position.y), orientation, this);
	maker.addFixture(m_body, 1.f, 1.f, 0.1f, false, &maker.createPolygonShape(b2Vec2(size.x, size.y)));

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setRotation(orientation);
	rec->setTextureRect(sf::IntRect(0, 0, (int)(size.x * 31), (int)(size.y * 31)));
	rec->setTexture(ResourceManager::getInstance()->getTexture(textureName));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool StaticBlock::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void StaticBlock::update(Game* game)
{
	
}