#include "GameObjects/Objects/Physics/Player.h"


/*! \file Player.cpp
* \brief CPP file for Player
*
* Implementation for Player
*
*/

/*!
\param world a b2World* - A pointer to the BOX2D world
*/
Player::Player(b2World* world)
	: PhysicsObject(world)
{
	// Set initial properties
	m_name = "Player";
	m_animated = true;

	// Create body
	respawnPlayer();

	// SFML Shape
	sf::RectangleShape* rec = new sf::RectangleShape;
	rec->setPosition(mk_spawnPoint);
	rec->setSize(mk_size);
	rec->setOrigin(mk_size * 0.5f);
	rec->setRotation(0);
	rec->setTextureRect(sf::IntRect(0, 0, 48, 70));
	rec->setTexture(ResourceManager::getInstance()->getTexture("player"));
	m_drawable = rec;

	// Attach to event listener
	EventListener::getInstance()->attach(this);
}

//! Constructor()
void Player::respawnPlayer()
{
	// If the body exists, destroy it
	if (m_body != nullptr)
	{
		m_world->DestroyBody(m_body);
		m_body = nullptr;
	}

	// Create physics properties
	PhysicsMaker maker;
	m_body = maker.createBody(m_world, b2BodyType::b2_dynamicBody, b2Vec2(mk_spawnPoint.x, mk_spawnPoint.y), 0, this);
	maker.addFixture(m_body, 0.6f, 0.f, 0.f, false, &maker.createPolygonShape(b2Vec2(mk_size.x, mk_size.y)));
	m_body->SetFixedRotation(true);

	// The player's foot sensor
	b2PolygonShape l_shape;
	l_shape.SetAsBox(0.20f, 0.05f, b2Vec2(0.f, 0.25f), 0);
	maker.addFixture(m_body, 0.1f, 0.f, 0.f, true, &l_shape);

	// Stop the respawn, used because respawning is in update function
	m_respawnPlayer = false;
}

/*!
\param pos a const sf::Vector2f - The point
\return a bool - Does the object contain the point
*/
bool Player::contains(sf::Vector2f pos)
{
	return false;
}

/*!
\param game a Game* - A pointer to the game
*/
void Player::update(Game* game)
{
	b2Vec2 pos = m_body->GetPosition();
	static_cast<sf::RectangleShape*>(m_drawable)->setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	static_cast<sf::RectangleShape*>(m_drawable)->setRotation(angle);

	if (m_applyReverseGravity)
	{
		// Apply 2x the reverse gravity strength to reverse the player's personal gravity to negate the worlds and replicate the same strength the other way
		m_body->ApplyForce(m_body->GetMass() * (2 * -m_world->GetGravity()), m_body->GetWorldCenter(), true);
	}

	if (m_rotateBody)
	{
		// Gravity switch has been hit, rotate the body 180 degrees
		m_body->SetTransform(m_body->GetPosition(), (180 - (m_body->GetAngle() * RAD2DEG)) * DEG2RAD);
		m_rotateBody = false;
	}

	if (m_respawnPlayer)
	{
		// Reduce lives by one
		m_lives--;
		m_applyReverseGravity = false;
		// If no lives are left, show game over scene
		if (m_lives == 0) { game->showScene("GameOver", false); }
		// Destroy and recreate body
		respawnPlayer();
	}

	if (m_JumpTimeout > 0)
	{
		// If cooldown has expired, decrease
		m_JumpTimeout--;
	}
}

/*!
\param game a Game* - A pointer to the game
\param key a const int - The key pressed
*/
void Player::keyPress(Game * game, const int key)
{
	if (key == sf::Keyboard::A)
	{
		move(1, b2Vec2(-2.f, m_body->GetLinearVelocity().y));
	}
	if (key == sf::Keyboard::D)
	{
		move(0, b2Vec2(2.f, m_body->GetLinearVelocity().y));
	}
}

/*!
\param game a Game* - A pointer to the game
\param key a const int - The key released
*/
void Player::keyRelease(Game* game, const int key)
{
	if (key == sf::Keyboard::Space && m_allowJump && m_JumpTimeout <= 0)
	{
		// If the space is pressed, the jump cooldown has expired and the player is on the ground, jump
		jump(m_applyReverseGravity);
		m_JumpTimeout = 30;
	}

	if (key == sf::Keyboard::A || key == sf::Keyboard::D)
	{
		// If movement keys are released, reset sprites and stop x axis movement
		move(-1, b2Vec2(0.f, m_body->GetLinearVelocity().y));
		m_spriteSheetIndex = 0;
		if(key == sf::Keyboard::A) { static_cast<sf::RectangleShape*>(m_drawable)->setTextureRect(sf::IntRect(0, 72 + (m_applyReverseGravity * 72), 49, 71)); }
		if (key == sf::Keyboard::D) { static_cast<sf::RectangleShape*>(m_drawable)->setTextureRect(sf::IntRect(0, 0 + (m_applyReverseGravity * 72), 49, 71)); }
	}
}

/*!
\param collider a PhysicsObject* - A pointer to the collding object
\param fixtureASensor a const bool - Is this object a sensor
\param fixtureBSensor a const bool - Is the colliding object a sensor
*/
void Player::enterCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor)
{
	// Get the colliding object's name and do appropriate action
	if (collider->getName() == "Gem" && !fixtureASensor)
	{
		m_gemsCollected++;
	}
	else if (collider->getName() == "Lava")
	{
		m_respawnPlayer = true;
	}
	else if (collider->getName() == "Key")
	{
		m_collectedKey = true;
	}
	else if (collider->getName() == "Door" && m_collectedKey && !fixtureASensor)
	{
		// Essentially kill the player
		// In future can add new win scene
		m_lives = 1;
		m_respawnPlayer = true;
		
	}
	else if (collider->getName() == "GravitySwitch" && !fixtureASensor)
	{
		// Switch has been hit, apply reverse gravity and rotate player
		m_applyReverseGravity = !m_applyReverseGravity;
		m_rotateBody = true;
	}
	else if (collider->getName() == "Enemy" && !fixtureASensor && !collider->getScheduleForDeletion())
	{
		// Kill player if enemy hits player's proper body and the enemy isnt scheduled for deletion
		m_respawnPlayer = true;
	}
	else if (fixtureASensor)
	{
		m_footCollisions++;
		m_allowJump = true;
	}
}

/*!
\param collider a PhysicsObject* - A pointer to the collding object
\param fixtureASensor a const bool - Is this object a sensor
\param fixtureBSensor a const bool - Is the colliding object a sensor
*/
void Player::leaveCollision(const PhysicsObject* collider, const bool fixtureASensor, const bool fixtureBSensor)
{
	if (fixtureASensor)
	{
		// Foot has left a collision, reduce count
		m_footCollisions--;
		// If foot isn't colliding with anything, disable jump
		if (m_footCollisions == 0)
		{
			m_allowJump = false;
		}
	}
}

//! animationUpdate()
void Player::animationUpdate()
{
	if (m_direction != -1)
	{
		// If the player is moving in a direction, apply correct sprite animation
		static_cast<sf::RectangleShape*>(m_drawable)->setTextureRect(sf::IntRect(m_spriteSheetIndex * 50, (m_direction * 72) + (m_applyReverseGravity * 72), 49, 71));
		m_spriteSheetIndex++;
		// Reset index as end of animation strip
		if (m_spriteSheetIndex == 3) { m_spriteSheetIndex = 0; }
	}
}

/*!
\param direction a const unsigned int - The direction of the player
\param velocity a const b2Vec2 - The movement velocity
*/
void Player::move(const unsigned int direction, const b2Vec2 velocity)
{
	m_direction = direction;
	// Apply force
	m_body->SetLinearVelocity(velocity);
	if (direction != -1)
	{
		// If a valid direction, update sprite
		static_cast<sf::RectangleShape*>(m_drawable)->setTextureRect(sf::IntRect(m_spriteSheetIndex * 50, (m_direction * 72) + (m_applyReverseGravity * 72), 49, 71));
	}
}

/*!
\param reverse a bool - Is reverse gravity being applied
*/
void Player::jump(const bool reverse)
{
	// If the player is currently in reverse gravity, reverse jump force
	if (reverse)
	{
		m_body->ApplyLinearImpulse(-mk_jumpStrength, m_body->GetWorldCenter(), true);
		return;
	}
	m_body->ApplyLinearImpulse(mk_jumpStrength, m_body->GetWorldCenter(), true);
}

/*!
\return an unsigned int - The number of gems collected by the player
*/
unsigned int Player::getGemsCollected() const
{
	return m_gemsCollected;
}

/*!
\return an unsigned int - The number of lives the player has
*/
unsigned int Player::getLives() const
{
	return m_lives;
}

/*!
\return a bool - Has the player collected the key
*/
bool Player::getKeyCollected() const
{
	return m_collectedKey;
}