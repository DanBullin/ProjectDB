#include "GameObjects/Objects/Physics/IronDoor.h"

/*! \file IronDoor.cpp
* \brief CPP file for IronDoor
*
* Implementation for IronDoor
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
\param position a const b2Vec2 - The position of the door
\param direction a const int - The direction of the door movement (-1 or 1)
*/
IronDoor::IronDoor(b2World * world, const b2Vec2 position, const int direction)
	: PhysicsObject(world)
{
	m_name = "IronDoor";
	m_open = false;
	m_direction = direction;
	m_motionTime = 75.f;
	m_elapsedTime = 0.f;

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_dynamicBody, position, 0, this);
	m_doorHinge = maker.createBody(m_world, b2BodyType::b2_staticBody, position, 0, this);

	maker.addFixture(m_body, 1.f, 0.01f, 0.1f, false, &maker.createPolygonShape(b2Vec2(0.25f, 1.f)));

	b2PolygonShape l_shape;
	l_shape.m_radius = 0.0f;
	l_shape.SetAsBox(0.125f, 0.125f, b2Vec2(0.f, -1.15f), 0.f);
	maker.addFixture(m_doorHinge, 1.f, 0.0f, 0.f, true, &l_shape);

	b2MotorJointDef jointDef;
	jointDef.Initialize(m_doorHinge, m_body);
	jointDef.maxForce = 1000.0f; // Force much large than we'd ever need
	jointDef.maxTorque = 1000.0f; // Avoid rotation with high torque
	m_doorMotor = (b2MotorJoint*)world->CreateJoint(&jointDef);
	
	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(position.x, position.y);
	rec->setSize(sf::Vector2f(0.25f, 1.f));
	rec->setOrigin(sf::Vector2f(0.25f, 1.f) * 0.5f);
	rec->setTexture(ResourceManager::getInstance()->getTexture("irondoor"));
	m_drawable = rec;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool IronDoor::contains(const sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void IronDoor::update(Game * game)
{
	if (m_open)
	{
		// If the door has been told to open, start movement
		m_elapsedTime++;
		float t = m_elapsedTime / m_motionTime;
		float dist;

		if (t <= 1.f)
		{
			// While t is less or equal to one, update linear offset
			dist = t * m_direction;
			m_doorMotor->SetLinearOffset(b2Vec2(0, dist));
		}
		else
		{
			// Door finished opening, stop opening
			m_open = false;
		}

		// Update position
		b2Vec2 pos = m_body->GetPosition();
		static_cast<sf::RectangleShape*>(m_drawable)->setPosition(pos.x, pos.y);
	}
}

//! open()
void IronDoor::open()
{
	// Set door to sensor so it can go inside static block
	m_open = true;
	m_body->GetFixtureList()->SetSensor(true);
}