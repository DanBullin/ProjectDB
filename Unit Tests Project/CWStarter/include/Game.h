#ifndef GAME_H
#define GAME_H
#pragma once

#include "Window.h"
#include "Events/EventListener.h"

#include "Scene/Scenes/MainMenu.h"
#include "Scene/Scenes/Level.h"
#include "Scene/Scenes/Pause.h"
#include "Scene/Scenes/GameOver.h"

/*! \file Game.h
* \brief Header file for Game
*
* Implementation for a Game
*/

/*! \class Game
\brief A Game
*/

/*! A Game Class */
class Game {
private:
	Window* m_window; //!< A pointer to the window which the game is drawn to
	std::map<std::string, Scene*> m_scenes; //!< A std::map containing a list of pointers to scenes mapped with a scene name
	std::string m_currentScene; //!< A string containing the name of the current scene
	sf::Clock m_gameClock; //!< A clock tracking time for game updating
	const float mk_gameTime = 1.f / 60.f; //!< The interval between game updates
public:
	Game(); //!< Constructor
	~Game(); //!< Destructor
	void initGame(); //!< Initialises the game
	Window* getWindow(); //!< Returns a pointer to the current window
	void updateView(); //!< Updates the game view with a new centre point
	GameObject* getObject(const std::string name); //!< Returns a pointer to the game object which holds the name passed
	Scene* getScene(const std::string name); //!< Returns the scene which holds the name passed
	Scene* createScene(const std::string name); //!< Returns a pointer to the scene which holds the name passed
	Scene* getCurrentScene(); //!< Returns a pointer to the current scene
	void destroyScheduledScenes(); //!< Destroys all scenes scheduled for deletion
	void showScene(const std::string sceneName, const bool deleteOld); //!< Shows the scene of the named passed, deletes the old scene if necassary

	void processInput(); //!< Process window events
	void update(); //!< Updates the game
};
#endif