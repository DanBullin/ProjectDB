#ifndef LAVA_H
#define LAVA_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file Lava.h
* \brief Header file for Lava
*
* Implementation for a Lava
*/

/*! \class Lava
\brief A Lava
*/

/*! A Lava Class */
class Lava : public PhysicsObject {
public:
	Lava(b2World* world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif