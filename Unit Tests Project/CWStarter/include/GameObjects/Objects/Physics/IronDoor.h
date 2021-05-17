#ifndef IRONDOOR_H
#define IRONDOOR_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file IronDoor.h
* \brief Header file for IronDoor
*
* Implementation for a IronDoor
*/

/*! \class IronDoor
\brief A IronDoor
*/

/*! A IronDoor Class */
class IronDoor : public PhysicsObject {
private:
	b2Body* m_doorHinge; //!< The body connected with the door body
	b2MotorJoint* m_doorMotor; //!< The door motor
	bool m_open; //!< Does the door need to open
	int m_direction; //!< The direction the door moves (-1 or 1)
	float m_motionTime; //!< The motion speed of door opening
	float m_elapsedTime; //!< The elapsed time used for motion speed
public:
	IronDoor(b2World* world, const b2Vec2 position, const int direction); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object

	void open(); //!< Opens the door
};
#endif