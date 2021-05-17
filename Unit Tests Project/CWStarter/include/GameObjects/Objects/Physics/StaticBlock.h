#ifndef STATICBLOCK_H
#define STATICBLOCK_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file StaticBlock.h
* \brief Header file for StaticBlock
*
* Implementation for a StaticBlock
*/

/*! \class StaticBlock
\brief A StaticBlock
*/

/*! A StaticBlock Class */
class StaticBlock : public PhysicsObject {
public:
	StaticBlock(b2World* world, const sf::Vector2f& position, const sf::Vector2f &size, const float orientation, const std::string textureName); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif