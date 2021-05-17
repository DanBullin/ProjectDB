#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "GameObjects/GameObject.h"
#include <algorithm>

/*! \file Scene.h
* \brief Header file for Scene
*
* Implementation for a Scene
*/

/*! \class Scene
\brief A Scene
*/

/*! A Scene Class */
class Scene : public sf::Drawable {
protected:
	std::string m_name = "Default"; //!< The name of the scene
	std::map<std::string, GameObject*> m_gameObjects; //!< Map containing pointers to Game Objects with a key mapped
	bool m_enabled; //!< Is the scene enabled
	bool m_markedDeletion = false; //!< Is the scene scheduled for deletion
	Game* m_game; //!< A pointer to the game
public:
	Scene(); //!< Constructor
	Scene(Game* game); //!< Constructor passing it a pointer to the game
	virtual ~Scene(); //!< Virtual Destructor
	virtual void initScene() = 0; //!< Pure virtual function for initialising scene

	void setEnabled(const bool enable); //!< Sets whether the scene is enabled
	bool getEnabled() const; //!< Gets whether the scene is enabled
	void scheduleForDeletion(const bool destroy); //!< Schedule the scene for deletion
	bool getScheduleForDeletion() const; //!< Gets whether the scene is scheduled for deletion

	virtual sf::Vector2f getSceneCentre(); //!< Gets the scene centre
	std::map<std::string, GameObject*>& getObjects(); //!< Gets a list of all the objects in the scene
	void updateObjects(); //!< Update all the objects in the scene

	virtual void clearScene(); //!< Clears the scene of all objects
	void destroyScheduledObjects(); //!< Destroys any scheduled objects

	virtual void update(const float& timestep) = 0; //!< Update the scene
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the scene
};
#endif