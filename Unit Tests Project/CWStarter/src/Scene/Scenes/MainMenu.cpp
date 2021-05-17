#include "Scene/Scenes/MainMenu.h"

/*! \file MainMenu.cpp
* \brief CPP file for MainMenu
*
* Implementation for MainMenu
*
*/

/*!
\param game a Game* - A pointer to the game
*/
MainMenu::MainMenu(Game* game)
	: Scene(game)
{
	// Set the scene name and disable the scene as no updating needs to be done
	m_name = "Main Menu";
	m_enabled = false;
}

//! Destructor()
MainMenu::~MainMenu()
{
	// Delete all heap allocated objects by clearing scene
	//LOG("Deleting scene: " + m_name);
	clearScene();
}

//! initScene()
void MainMenu::initScene()
{
	// Creates all objects in the Main Menu
	m_gameObjects["Background"] = new StaticImage(sf::Vector2f(-4.f, -3.f), sf::Vector2f(8.f, 6.f), sf::Vector2f(1.f, 1.f), "menubackground");
	m_gameObjects["Logo"] = new StaticImage(sf::Vector2f(-1.f, -3.f), sf::Vector2f(200.f, 200.f), sf::Vector2f(0.01f, 0.01f), "logo");
	m_gameObjects["Play"] = new DynamicText("Play", sf::Vector2f(-0.49f, -0.5f), 50, 1);
	m_gameObjects["Quit"] = new DynamicText("Quit", sf::Vector2f(-0.45f, 0.5f), 50, 4);
	m_gameObjects["Creation"] = new StaticText("IMAT2906 Coursework                                       Created by Dan Bullin", sf::Vector2f(-3.8f, 2.6f), 24, sf::Color::White);
}

/*!
\param timestep a const float& - The game update timestep
*/
void MainMenu::update(const float& timestep)
{
	// No update happens and because m_enabled is false, this is never called
}