#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#pragma once

#include "Box2D/Box2D.h"
#include "GameObject.h"
#include "GameObjects/PhysicsMaker.h"

#define DEG2RAD 0.017453f //!< Scalar to convert degrees to radians
#define RAD2DEG 57.29577f //!< Scalar to covert radians to degrees

/*! \file PhysicsObject.h
* \brief Header file for PhysicsObject
*
* Implementation for a PhysicsObject
*/

/*! \class PhysicsObject
\brief A PhysicsObject
*/

/*! A PhysicsObject Class */
class PhysicsObject : public GameObject {
protected:
	b2World* m_world; //!< The physics world
	b2Body* m_body; //!< Box2D body, no need to delete this as BOX2D will look after it
public:
	PhysicsObject(b2World* world); //!< Constructor
	~PhysicsObject(); //!< Destructor
	void setUserData(void* data); //!< Set the userdata of the body
	virtual void enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor); //!< Action to run when this object collides
	virtual void leaveCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor); //!< Action to run when this object leaves a collision
};
#endif