#include "GameObjects/PhysicsMaker.h"

/*! \file PhysicsMaker.cpp
* \brief CPP file for PhysicsMaker
*
* Implementation for PhysicsMaker
*
*/

//! Constructor()
PhysicsMaker::PhysicsMaker()
{
}

/*!
\param world a b2World* - A pointer to the world
\param bodyType a const b2BodyType - The body type
\param position a const b2Vec2 - The position of the body
\param angle a const float - The angle of the body
\param userData a void* - A pointer to the data to store in the body
\return a b2Body* - A pointer to the created body
*/
b2Body * PhysicsMaker::createBody(b2World* world, const b2BodyType bodyType, const b2Vec2 position, const float angle, void * userData)
{
	b2BodyDef l_bodyDef;
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.type = bodyType;
	l_bodyDef.angle = angle * DEG2RAD;
	l_bodyDef.userData = userData;
	return world->CreateBody(&l_bodyDef);
}

/*!
\param body a b2Body* - A pointer to the body you're adding a fixture to
\param density a const float - The density of the fixture
\param friction a const float - The amount of friction the fixture has
\param restitution a const float - The amount of restitution the fixture has
\param sensor a const bool - Is the fixture a sensor
\param shape a b2Shape* - A pointer to the shape of the fixture
*/
void PhysicsMaker::addFixture(b2Body * body, const float density, const float friction, const float restitution, const bool sensor, b2Shape * shape)
{
	b2FixtureDef l_fixtureDef;
	l_fixtureDef.density = density;
	l_fixtureDef.friction = friction;
	l_fixtureDef.restitution = restitution;
	l_fixtureDef.isSensor = sensor;
	l_fixtureDef.shape = shape;
	body->CreateFixture(&l_fixtureDef);
}

/*!
\param size a const b2Vec2 - The size of the shape
\param radius a const float - The radius of the shape
\return a b2PolygonShape - The polygon shape created
*/
b2PolygonShape PhysicsMaker::createPolygonShape(const b2Vec2 size, const float radius)
{
	b2PolygonShape l_shape;
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;
	return l_shape;
}

/*!
\param radius a const float - The radius of the circle
\return a b2CircleShape - The circle shape created
*/
b2CircleShape PhysicsMaker::createCircle(const float radius)
{
	b2CircleShape l_circ;
	l_circ.m_radius = radius;
	return l_circ;
}
