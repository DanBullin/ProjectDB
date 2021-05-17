#include "Game.h"

/*! \file Game.cpp
* \brief CPP file for Game
*
* Implementation for Game
*
*/

//! Constructor()
Game::Game()
{
	// Initialise the game
	initGame();
}

//! Destructor()
Game::~Game()
{
	//LOG("Deleting the world, window and objects...");
	// Destroy the window if it's a valid pointer
	if (m_window != nullptr) { delete m_window; }
	m_window = nullptr;
	// Destroy all scenes
	for (auto s : m_scenes)
	{
		delete s.second;
	}
	m_scenes.clear(); // Clear scenes map
}

//! initGame()
void Game::initGame()
{
	// Load all assets (textures & fonts)
	ResourceManager::getInstance()->loadAllAssets();
	// Create a new window
	m_window = new Window;
	// Create the main menu scene and set that as the current scene
	m_currentScene = "MainMenu";
	m_scenes["MainMenu"] = new MainMenu(this);
	// Initialise the current scene
	getCurrentScene()->initScene();
}

/*!
\return a Window* - The game window
*/
Window* Game::getWindow()
{
	return m_window;
}

//! updateView()
void Game::updateView()
{
	// Update the game view's centre by retrieving scene centre from the current scene
	// Level's centre is based on player's position thereby the player is always centre frame
	m_window->getGameView().setCenter(getCurrentScene()->getSceneCentre());
}

/*!
\param name a const std::string - The name of the object desired
\return a GameObject* - A pointer to the object desired
*/
GameObject* Game::getObject(const std::string name)
{
	// Get the list of objects from the current scene
	auto& objects = getCurrentScene()->getObjects();
	// If it doesn't find the object name, object isnt in the scene
	if (objects.find(name) == objects.end())
	{
		return nullptr;
	}
	return getCurrentScene()->getObjects()[name];
}

/*!
\param name a const std::string - The name of the scene to be created
\return a Scene* - A pointer to the scene created
*/
Scene* Game::createScene(const std::string name)
{
	Scene* scene;
	// Checks the desired scene name and creates the relevant scene type
	if (name == "MainMenu")
	{
		scene = new MainMenu(this);
	}
	else if (name == "Level")
	{
		scene = new Level(this);
	}
	else if (name == "Pause")
	{
		scene = new Pause(this);
	}
	else if (name == "GameOver")
	{
		scene = new GameOver(this);
	}
	else
	{
		// If an invalid scene name was passed, return a null pointer
		return nullptr;
	}
	// Return pointer to the new scene
	return scene;
}

/*!
\return a Scene* - A pointer to the current scene
*/
Scene* Game::getCurrentScene()
{
	// If the current scene doesn't exist, create it
	// Otherwise return a pointer to it
	if (m_scenes.find(m_currentScene) == m_scenes.end())
	{
		m_scenes[m_currentScene] = createScene(m_currentScene);
	}
	return m_scenes.at(m_currentScene);
}

/*!
\param name a const std::string - The name of the scene desired
\return a Scene* - A pointer to the scene desired
*/
Scene* Game::getScene(const std::string name)
{
	// If the scene doesn't exist, return a null pointer
	if (m_scenes.find(name) == m_scenes.end())
	{
		return nullptr;
	}
	return m_scenes.at(name);
}

//! destroyScheduledScenes()
void Game::destroyScheduledScenes()
{
	// Loop through all scenes and if it's scheduled for deletion
	// Delete memory and erase element from map
	for (auto& it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{
		if (it->second->getScheduleForDeletion())
		{
			delete it->second;
			m_scenes.erase(it);
			// Iterator is invalidated, break.
			break;
		}
	}
}

/*!
\param sceneName a const std::string - The name of the scene desired
\param deleteOld a const bool - Delete the old scene
*/
void Game::showScene(const std::string sceneName, const bool deleteOld)
{
	// If we have to delete the old scene, free up the memory and erase from the map
	if (deleteOld)
	{
		delete getCurrentScene();
		m_scenes.erase(m_currentScene);
	}
	// Set the current scene to the new name
	m_currentScene = sceneName;
	// If the scene hasn't been initialised, initialise it
	if (getCurrentScene()->getObjects().size() == 0)
	{
		getCurrentScene()->initScene();
		updateView();
	}
	// If its the level, restart all clocks
	if (sceneName == "Level")
	{
		((Level*)(getCurrentScene()))->restartClocks();
	}
	// Enable the current scene, may of been disabled previously if its not a new scene
	getCurrentScene()->setEnabled(true);
}

//! processInput()
void Game::processInput()
{
	sf::Event event;
	// Check all window events
	while (m_window->pollEvent(event))
	{
		// If the window close button was pressed, close window
		if (event.type == sf::Event::Closed) { m_window->close(); }

		// If the mouse moved, button pressed or button released
		if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
		{
			// Get mouse position and convert based on the view size
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
			sf::Vector2f convertedPos = sf::Vector2f(m_window->mapPixelToCoords(mousePos).x, m_window->mapPixelToCoords(mousePos).y);
			EventListener::getInstance()->notify(this, event.type, convertedPos);
		}

		// If the key pressed or released
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			EventListener::getInstance()->notify(this, event.type, event.key.code);
		}
	}
	// Update all subscribing objects to update based on continuous input (Such as key held stuff, mouse held)
	EventListener::getInstance()->update(this);
}

//! update()
void Game::update()
{
	// While the window is open
	while (m_window->isOpen())
	{
		// Clear the background
		m_window->clear(m_window->getWindowInfo().mk_backgroundColour);
		// Limit game updates by the set time interval
		float fElapsedTime = m_gameClock.getElapsedTime().asSeconds();
		if (fElapsedTime > mk_gameTime)
		{
			// Process any input/event
			processInput();
			// Update the current scene
			getCurrentScene()->update(fElapsedTime);
			// Destroy any scheduled scenes
			destroyScheduledScenes();
			// Update the window view, set it and draw
			updateView();
			m_gameClock.restart();
		}

		m_window->setGameView();
		m_window->draw(*getCurrentScene());
		m_window->display();
	}
}