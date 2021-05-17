#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file MovingPlatform.h
* \brief Header file for MovingPlatform
*
* Implementation for a MovingPlatform
*/

/*! \class MovingPlatform
\brief A MovingPlatform
*/

/*! A MovingPlatform Class */
class MovingPlatform : public PhysicsObject {
private:
	b2Vec2 m_velocity; //!< The velocity movement
	unsigned int m_maxTime; //!< The max time when velocity must change
	unsigned int m_currentTime; //!< The current time in movement sequence
public:
	MovingPlatform(b2World* world, const float posX, const float posY, const b2Vec2 velocity, const unsigned int maxTime); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif