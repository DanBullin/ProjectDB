#ifndef BOX_H
#define BOX_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file Box.h
* \brief Header file for Box
*
* Implementation for a Box
*/

/*! \class Box
\brief A Box
*/

/*! A Box Class */
class Box : public PhysicsObject {
public:
	Box(b2World* world, const sf::Vector2f& position, const sf::Vector2f &size); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif