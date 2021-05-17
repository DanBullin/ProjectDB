#include "Physics/ContactListener.h"
#include "Scene/Scenes/Level.h"

/*! \file ContactListener.cpp
* \brief CPP file for ContactListener
*
* Implementation for a ContactListener
*
*/

//! Constructor()
ContactListener::ContactListener()
{
}

/*!
\param contact a b2Contact* - A pointer to the contact info
*/
void ContactListener::BeginContact(b2Contact * contact)
{
	// Get both colliding fixtures body's and its user data
	void* dataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* dataB = contact->GetFixtureB()->GetBody()->GetUserData();

	// If there was no user data, just end collision response
	if (dataA == nullptr || dataB == nullptr)
	{
		return;
	}

	// If user data is found, cast the user data to PhysicsObject
	PhysicsObject* objectA = static_cast<PhysicsObject*>(dataA);
	PhysicsObject* objectB = static_cast<PhysicsObject*>(dataB);
	// Store whether either colliding fixture is a sensor
	bool isASensor = contact->GetFixtureA()->IsSensor();
	bool isBSensor = contact->GetFixtureB()->IsSensor();

	// Call PhysicsObject.enter/leave function passing the other object, and whether either is a sensor
	// All objects derive from PhysicsObject and each object overrides the collision functions to have their own unique collision response
	objectA->enterCollision(objectB, isASensor, isBSensor);
	objectB->enterCollision(objectA, isBSensor, isASensor);
}

/*!
\param contact a b2Contact* - A pointer to the contact info
*/
void ContactListener::EndContact(b2Contact * contact)
{
	// Get both colliding fixtures body's and its user data
	void* dataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* dataB = contact->GetFixtureB()->GetBody()->GetUserData();

	// If there was no user data, just end collision response
	if (dataA == nullptr || dataB == nullptr)
	{
		return;
	}

	// If user data is found, cast the user data to PhysicsObject
	PhysicsObject* objectA = static_cast<PhysicsObject*>(dataA);
	PhysicsObject* objectB = static_cast<PhysicsObject*>(dataB);
	// Store whether either colliding fixture is a sensor
	bool isASensor = contact->GetFixtureA()->IsSensor();
	bool isBSensor = contact->GetFixtureB()->IsSensor();

	// Call PhysicsObject.enter/leave function passing the other object, and whether either is a sensor
	objectA->leaveCollision(objectB, isASensor, isBSensor);
	objectB->leaveCollision(objectA, isBSensor, isASensor);
}