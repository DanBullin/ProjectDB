#ifndef GEM_H
#define GEM_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file Gem.h
* \brief Header file for Gem
*
* Implementation for a Gem
*/

/*! \class Gem
\brief A Gem
*/

/*! A Gem Class */
class Gem : public PhysicsObject {
public:
	Gem(b2World* world, const sf::Vector2f& position); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
	void enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor) override; //!< Enter collision action when this object collides
};
#endif