#ifndef PHYSICSMAKER_H
#define PHYSICSMAKER_H
#pragma once

#include "Box2D/Box2D.h"

#define DEG2RAD 0.017453f //!< Scalar to convert degrees to radians
#define RAD2DEG 57.29577f //!< Scalar to covert radians to degrees

/*! \file PhysicsMaker.h
* \brief Header file for PhysicsMaker
*
* Implementation for a PhysicsMaker
*/

/*! \class PhysicsMaker
\brief A PhysicsMaker
*/

/*! A PhysicsMaker Class */
class PhysicsMaker {
public:
	PhysicsMaker(); //!< Constructor
	b2Body* createBody(b2World* world, const b2BodyType bodyType, const b2Vec2 position, const float angle, void* userData); //!< Creates a body and adds to the world
	void addFixture(b2Body* body, const float density, const float friction, const float restitution, const bool sensor, b2Shape* shape); //!< Adds fixture to the body
	b2PolygonShape createPolygonShape(const b2Vec2 size, const float radius = 0.f); //!< Creates a polygon shape
	b2CircleShape createCircle(const float radius); //!< Creates a circle shape
};
#endif