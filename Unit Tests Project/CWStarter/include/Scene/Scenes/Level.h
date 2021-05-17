#ifndef LEVEL_H
#define LEVEL_H
#pragma once

#include "Scene/Scene.h"
#include "Maths/VectorDistance.h"
#include "Physics/SFMLDebugDraw.h"
#include "GameObjects/Objects/StaticImage.h"
#include "GameObjects/Objects/UI/DynamicText.h"
#include "GameObjects/Objects/UI/KeyIcon.h"
#include "GameObjects/Objects/UI/StaticText.h"
#include "GameObjects/Objects/Physics/StaticBlock.h"
#include "GameObjects/Objects/Physics/Player.h"
#include "GameObjects/Objects/Physics/MovingPlatform.h"
#include "GameObjects/Objects/Physics/RevolvingPlatform.h"
#include "GameObjects/Objects/Physics/Gem.h"
#include "GameObjects/Objects/Physics/Lava.h"
#include "GameObjects/Objects/Physics/GravitySwitch.h"
#include "GameObjects/Objects/Physics/Box.h"
#include "GameObjects/Objects/Physics/Key.h"
#include "GameObjects/Objects/Physics/Door.h"
#include "GameObjects/Objects/Physics/Enemy.h"
#include "GameObjects/Objects/Physics/IronDoor.h"
#include "GameObjects/Objects/Physics/DoorSensor.h"
#include "Physics/ContactListener.h"

/*! \file Level.h
* \brief Header file for Level
*
* Implementation for a Level
* Inherits from Scene and creates the necassary objects
*/

/*! \class Level
\brief A Level
*/

/*! A Level Class */
class Level : public Scene {
private:
	b2World* m_world; //!< The physics world
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 mk_gravity = b2Vec2(0.f, 9.81f); //!< Standard earth gravity will be used (negate the value ofcourse!)
	ContactListener m_contactListener; //!< The contact listener for the fixtures in the world
	SFMLDebugDraw m_physicsDraw; //!< Draws the bodies in the world
	bool m_drawBodies; //!< Condition dictating whether to draw the physical bodies

	sf::Clock m_animationClock; //!< Clock used for animation updating
	const float mk_AnimationTime = 1.f / 5.f; //!< Animation time interval

	void updateStatics(); //!< Updates the statics for the level (HUD)
	sf::Vector2f getSceneCentre() override; //!< Returns an updated scene centre based on player position
	void disableObjectRender(); //!< Disables drawing of objects outside render range
	void createStatics(); //!< Creates the static objects
	void createEnvironment(); //!< Creates the enviroment objects
	void createGems(); //!< Creates the collectable gems
public:
	Level(Game* game); //!< Constructor
	~Level(); //!< Destructor
	void initScene() override; //!< Initialise the level
	void setPhysicsDraw(const bool draw); //!< Set whether to draw the raw physics components
	bool getPhysicsDraw() const; //!< Returns whether to draw the raw physics components
	void clearScene() override; //!< Clears the level
	void restartClocks(); //!< Restarts the animation clock
	void update(const float& timestep) override; //!< Update the level
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //!< Draw the level
};
#endif