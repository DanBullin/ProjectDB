#include "GameObjects/PhysicsObject.h"

/*! \file PhysicsObject.cpp
* \brief CPP file for PhysicsObject
*
* Implementation for PhysicsObject
*
*/

/*!
\param world a b2World* - A pointer to the Box2D world
*/
PhysicsObject::PhysicsObject(b2World* world)
{
	// Set initial properties
	m_world = world;
	m_body = nullptr;
}

//! Destructor()
PhysicsObject::~PhysicsObject()
{
	// Destroy body from world
	m_world->DestroyBody(m_body);
	// Set pointers to null
	m_body = nullptr;
	m_world = nullptr;
}

/*!
\param data a void* - A pointer to the data to store
*/
void PhysicsObject::setUserData(void* data)
{
	m_body->SetUserData(data);
}

/*!
\param collider a const PhysicsObject* - A pointer to the colliding object
\param fixtureASensor a const bool - Is this object a sensor
\param fixtureBSensor a const bool - Is this colliding object a sensor
*/
void PhysicsObject::enterCollision(const PhysicsObject * collider, const bool fixtureASensor, const bool fixtureBSensor)
{
}

/*!
\param collider a const PhysicsObject* - A pointer to the colliding object
\param fixtureASensor a const bool - Is this object a sensor
\param fixtureBSensor a const bool - Is this colliding object a sensor
*/
void PhysicsObject::leaveCollision(const PhysicsObject * collider, const bool fixtureASensor, const bool fixtureBSensor)
{
}