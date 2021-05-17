#ifndef DOOR_H
#define DOOR_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file Door.h
* \brief Header file for Door
*
* Implementation for a Door
*/

/*! \class Door
\brief A Door
*/

/*! A Door Class */
class Door : public PhysicsObject {
private:
	bool m_updatedTexture; //!< Has the door texture been updated, used to stop updating once it has
public:
	Door(b2World* world, const sf::Vector2f& position); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif