#include "GameObjects/Objects/Physics/RevolvingPlatform.h"

/*! \file RevolvingPlatform.cpp
* \brief CPP file for RevolvingPlatform
*
* Implementation for RevolvingPlatform
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param posX a const float - The x position
\param posY a const float - The y position
\param rotation a const float - The rotation of the revolving platform
*/
RevolvingPlatform::RevolvingPlatform(b2World* world, const float posX, const float posY, const float rotation)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "RevolvingPlatform";
	sf::Vector2f size = sf::Vector2f(1.28f, 0.32f);

	// Create physics properties including anchor
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_dynamicBody, b2Vec2(posX, posY), rotation, this);
	maker.addFixture(m_body, 2.5f, 0.f, 0.f, false, &maker.createPolygonShape(b2Vec2(size.x, size.y)));
	m_anchor = maker.createBody(m_world, b2BodyType::b2_staticBody, b2Vec2(posX, posY), rotation, this);
	maker.addFixture(m_anchor, 0.f, 0.f, 0.f, false, &maker.createCircle(0.01f));

	// Set angular damping
	m_body->SetAngularDamping(1.5f);

	// Create the joint
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_anchor;
	jointDef.bodyB = m_body;
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0.f, 0.f);
	jointDef.localAnchorB.Set(0.f, 0.f);
	m_hinge = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(posX, posY);
	rec->setSize(size);
	rec->setOrigin(size * 0.5f);
	rec->setRotation(rotation);
	rec->setTextureRect(sf::IntRect(0, 0, 128, 30));
	rec->setTexture(ResourceManager::getInstance()->getTexture("platform"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool RevolvingPlatform::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void RevolvingPlatform::update(Game* game)
{
	// Only update angle
	float angle = m_body->GetAngle()* RAD2DEG;
	static_cast<sf::RectangleShape*>(m_drawable)->setRotation(angle);
}
