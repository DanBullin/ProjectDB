#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include "GameObjects/PhysicsObject.h"

/*! \file Enemy.h
* \brief Header file for Enemy
*
* Implementation for a Enemy
*/

/*! \class Enemy
\brief A Enemy
*/

/*! A Enemy Class */
class Enemy : public PhysicsObject {
private:
	b2Vec2 m_velocity; //!< The movement velocity
	bool m_direction; //!< The left/right direction of the enemy. 0 for Left, 1 for Right
	float m_currentTime; //!< The current time in movement sequence
	float m_maxTime; //!< The maximum time in a movement sequence
	unsigned int m_spriteSheetIndex; //!< The current sprite sheet index, used for animation
public:
	Enemy(b2World* world, const float posX, const float posY, const b2Vec2 velocity, const float maxTime); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
	void enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor) override; //!< Enter collision action when this object collides
	void animationUpdate() override; //!< The animation update
};
#endif