#include "Scene/Scene.h"

/*! \file Scene.cpp
* \brief CPP file for Scene
*
* Implementation for Scene
*
*/

//! Constructor()
Scene::Scene()
{
	// Set enabled to false by default
	m_enabled = false;
}

/*!
\param game a Game* - A pointer to the game
*/
Scene::Scene(Game * game)
{
	m_game = game;
}

//! Destructor()
Scene::~Scene()
{
	// ClearScene destorys all heap allocated stuff and thats handled in sub class destructor
}

/*!
\param enable a const bool - Enable the scene
*/
void Scene::setEnabled(const bool enable)
{
	m_enabled = enable;
}

/*!
\return a bool - Returns if the scene is enabled
*/
bool Scene::getEnabled() const
{
	return m_enabled;
}

/*!
\param destroy a const bool - Destroy the scene
*/
void Scene::scheduleForDeletion(const bool destroy)
{
	m_markedDeletion = destroy;
}

/*!
\return a bool - Returns if scene should be destroyed
*/
bool Scene::getScheduleForDeletion() const
{
	return m_markedDeletion;
}

/*!
\return a sf::Vector2f - Returns the centre point of the current scene
*/
sf::Vector2f Scene::getSceneCentre()
{
	return sf::Vector2f(0.f, 0.f);
}

/*!
\return a std::map<std::string, GameObject*>& - Returns a reference to a map of game objects of the scene
*/
std::map<std::string, GameObject*>& Scene::getObjects()
{
	return m_gameObjects;
}

//! updateObjects()
void Scene::updateObjects()
{
	// Loop through all game objects and call their update
	for (auto& g : m_gameObjects)
	{
		// only if the object is enabled
		if (g.second->getEnabled())
		{
			g.second->update(m_game);
		}
	}
}

//! clearScene()
void Scene::clearScene()
{
	// Destroys all heap allocated objects in the scene
	LOG("Clearing scene: " + m_name);
	for (auto& g : m_gameObjects)
	{
		delete g.second;
	}
	m_gameObjects.clear();
}

//! destroyScheduledObjects()
void Scene::destroyScheduledObjects()
{
	for (auto& it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		// If the object is scheduled to be deleted
		if (it->second->getScheduleForDeletion())
		{
			// Delete it and erase it from map
			delete it->second;
			m_gameObjects.erase(it);
			break;
		}
	}
}

/*!
\param target a sf::RenderTarget & - A reference to the RenderTarget
\param states a sf::RenderStates - A render state
*/
void Scene::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& g : m_gameObjects)
	{
		// Draw the object
		// Object itself handles whether it's draw is enabled
		target.draw(*g.second);
	}
}