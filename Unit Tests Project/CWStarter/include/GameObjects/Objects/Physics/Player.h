#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "GameObjects/PhysicsObject.h"
#include "Events/EventListener.h"

/*! \file Player.h
* \brief Header file for Player
*
* Implementation for a Player
*/

/*! \class Player
\brief A Player
*/

/*! A Player Class */
class Player : public PhysicsObject {
private:
	sf::Vector2f mk_spawnPoint = sf::Vector2f(0.f, 0.f); //!< The spawn location of the player
	const sf::Vector2f mk_size = sf::Vector2f(0.5f, 0.5f); //!< The size of the player
	const b2Vec2 mk_jumpStrength = b2Vec2(0, -0.92f); //!< The jump strength of the player

	int m_gemsCollected = 0; //!< Number of gems collected
	unsigned int m_lives = 3; //!< Number of player lives
	bool m_collectedKey = false; //!< Has the key been collected
	bool m_applyReverseGravity = false; //!< Apply a reverse gravity force to the player

	bool m_respawnPlayer = false; //!< Should the player respawn
	bool m_rotateBody = false; //!< Should the body of the player be rotated
	bool m_allowJump = true; //!< Condition if the player can jump
	unsigned int m_footCollisions = 0; //!< The number of collisions with the player's feet
	int m_JumpTimeout = 0; //!< The timeout time between jumps
	unsigned int m_spriteSheetIndex = 0; //!< The current animation sprite index
	int m_direction = -1; //!< The direction of the player

	void respawnPlayer(); //!< Repawn the player
	void move(const unsigned int direction, const b2Vec2 velocity); //!< Apply x axis movement force
	void jump(const bool reverse); //!< Apply jump force
public:
	Player(b2World* world); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
	void enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor) override; //!< Enter collision action when this object collides
	void leaveCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor) override; //!< Leave collision action when this object collides
	void keyPress(Game* game, const int key) override; //!< Action to run when a key is pressed. Must attach to the EventListener
	void keyRelease(Game* game, const int key) override; //!< Action to run when a key is released. Must attach to the EventListener
	void animationUpdate() override; //!< The animation update

	unsigned int getGemsCollected() const; //!< Get the number of gems collected
	unsigned int getLives() const; //!< Get the number of player lives
	bool getKeyCollected() const; //!< Get if the key has been collected
};
#endif