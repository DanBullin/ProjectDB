#include "Scene/Scenes/GameOver.h"

/*! \file GameOver.cpp
* \brief CPP file for GameOver
*
* Implementation for GameOver
*
*/

/*!
\param game a Game* - A pointer to the game
*/
GameOver::GameOver(Game* game)
	: Scene(game)
{
	// Set the scene name and disable the scene as no updating needs to be done
	m_name = "GameOver";
	m_enabled = false;
}

//! Destructor()
GameOver::~GameOver()
{
	// Delete all heap allocated objects by clearing scene
	LOG("Deleting scene: " + m_name);
	clearScene();
}

//! initScene()
void GameOver::initScene()
{
	// Creates all objects in the Main Menu
	m_gameObjects["Background"] = new StaticImage(sf::Vector2f(-4.f, -3.f), sf::Vector2f(8.f, 6.f), sf::Vector2f(1.f, 1.f), "menubackground");
	m_gameObjects["GameOver"] = new StaticText("GAME OVER", sf::Vector2f(-1.47f, -2.f), 48, sf::Color::White);
	m_gameObjects["GemIcon"] = new StaticImage(sf::Vector2f(-0.93f, -0.5f), sf::Vector2f(0.32f, 0.32f), sf::Vector2f(1.f, 1.f), "gem");
	m_gameObjects["GemsCollected"] = new StaticText("Collected: x", sf::Vector2f(-0.53f, -0.47f), 24, sf::Color::White);
	m_gameObjects["Quit"] = new DynamicText("Quit", sf::Vector2f(-0.45f, 0.5f), 50, 3);
	// Set the gems collected text to the number of gems the player collected
	sf::Text* gemsCollectedtmp = static_cast<sf::Text*>(m_gameObjects["GemsCollected"]->getDrawable());
	gemsCollectedtmp->setString("Collected: x" + std::to_string(((Player*)(m_game->getScene("Level")->getObjects()["Player"]))->getGemsCollected()));
}

/*!
\param timestep a const float& - The game update timestep
*/
void GameOver::update(const float& timestep)
{
	// No update happens and because m_enabled is false, this is never called
}