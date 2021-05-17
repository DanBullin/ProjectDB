#ifndef DOORSENSOR_H
#define DOORSENSOR_H
#pragma once

#include "GameObjects/PhysicsObject.h"
#include "GameObjects/Objects/Physics/IronDoor.h"

/*! \file DoorSensor.h
* \brief Header file for DoorSensor
*
* Implementation for a DoorSensor
*/

/*! \class DoorSensor
\brief A DoorSensor
*/

/*! A DoorSensor Class */
class DoorSensor : public PhysicsObject {
private:
	IronDoor* m_door1; //!< The first door connected to the sensor
	IronDoor* m_door2; //!< The second door connected to the sensor
public:
	DoorSensor(b2World* world, const sf::Vector2f& position, IronDoor* door1, IronDoor* door2); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
	void enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor) override; //!< Enter collision action when this object collides
};
#endif