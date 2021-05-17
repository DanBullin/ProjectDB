#ifndef KEY_H
#define KEY_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file Key.h
* \brief Header file for Key
*
* Implementation for a Key
*/

/*! \class Key
\brief A Key
*/

/*! A Key Class */
class Key : public PhysicsObject {
public:
	Key(b2World* world, const sf::Vector2f& position); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
	void enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor) override; //!< Enter collision action when this object collides
};
#endif