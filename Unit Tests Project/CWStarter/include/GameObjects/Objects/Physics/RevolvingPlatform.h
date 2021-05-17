#ifndef REVOLVINGPLATFORM_H
#define REVOLVINGPLATFORM_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file RevolvingPlatform.h
* \brief Header file for RevolvingPlatform
*
* Implementation for a RevolvingPlatform
*/

/*! \class RevolvingPlatform
\brief A RevolvingPlatform
*/

/*! A RevolvingPlatform Class */
class RevolvingPlatform : public PhysicsObject {
private:
	b2Body * m_anchor; //!< The anchor body for the revolute joint
	b2RevoluteJoint * m_hinge; //!< The revolute joint pointer
public:
	RevolvingPlatform(b2World* world, const float posX, const float posY, const float rotation); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif