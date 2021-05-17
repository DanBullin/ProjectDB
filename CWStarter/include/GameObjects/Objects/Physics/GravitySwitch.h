#ifndef GRAVITYSWITCH_H
#define GRAVITYSWITCH_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file GravitySwitch.h
* \brief Header file for GravitySwitch
*
* Implementation for a GravitySwitch
*/

/*! \class GravitySwitch
\brief A GravitySwitch
*/

/*! A GravitySwitch Class */
class GravitySwitch : public PhysicsObject {
public:
	GravitySwitch(b2World* world, const sf::Vector2f& position); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif