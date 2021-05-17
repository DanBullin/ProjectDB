#ifndef KEYICON_H
#define KEYICON_H
#pragma once

#include "GameObjects/GameObject.h"
#include "Game.h"
#include "Events/EventListener.h"

/*! \file KeyIcon.h
* \brief Header file for KeyIcon
*
* Implementation for a KeyIcon
*/

/*! \class KeyIcon
\brief A KeyIcon
*/

/*! A KeyIcon Class */
class KeyIcon : public GameObject {
private:
	bool m_updatedTexture; //!< Has the texture ever been updated
public:
	KeyIcon(); //!< Constructor
	bool contains(sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif