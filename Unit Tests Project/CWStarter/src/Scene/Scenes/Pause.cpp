#include "Scene/Scenes/Pause.h"

/*! \file Pause.cpp
* \brief CPP file for Pause
*
* Implementation for Pause
*
*/

/*!
\param game a Game* - A pointer to the game
*/
Pause::Pause(Game* game)
	: Scene(game)
{
	// Set the scene name and disable the scene as no updating needs to be done
	m_name = "Pause";
	m_enabled = false;
}

//! Destructor()
Pause::~Pause()
{
	// Delete all heap allocated objects by clearing scene
	//LOG("Deleting scene: " + m_name);
	clearScene();
}

//! initScene()
void Pause::initScene()
{
	// Creates all objects in the Main Menu
	m_gameObjects["Background"] = new StaticImage(sf::Vector2f(-4.f, -3.f), sf::Vector2f(8.f, 6.f), sf::Vector2f(1.f, 1.f), "menubackground");
	m_gameObjects["Paused"] = new StaticText("PAUSED", sf::Vector2f(-0.98f, -2.f), 48, sf::Color::White);
	m_gameObjects["Resume"] = new DynamicText("Resume", sf::Vector2f(-0.94f, -0.5f), 50, 1);
	m_gameObjects["Quit"] = new DynamicText("Quit", sf::Vector2f(-0.45f, 0.5f), 50, 3);
}

/*!
\param timestep a const float& - The game update timestep
*/
void Pause::update(const float& timestep)
{
}
