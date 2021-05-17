#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SFML/Graphics.hpp>

/*! \file Window.h
* \brief Header file for Window
*
* Implementation for a SFML window
*/

/*! \class Window
\brief A SFML Window
*/

//! \struct WindowInfo
struct WindowInfo
{
	const std::string mk_titleText = "Project DB - Daniel Bullin"; //!< Title of the Window
	const sf::Vector2u mk_WindowSize = sf::Vector2u(800, 600); //!< Window size
	const sf::Color mk_backgroundColour = sf::Color::White; //!< Window background colour
	bool m_enableVSync = false; //!< Window setting for whether VSync is enabled
	unsigned int m_maxFramerate = 120; //!< Window setting for maximum framerate
};

/*! A Window Class */
class Window : public sf::RenderWindow {
private:
	WindowInfo m_windowInfo; //!< Window structure containing info about the window
	sf::View m_view; //!< The view or 2D camera attached to the window
public:
	Window(); //!< Constructor
	~Window(); //!< Destructor
	void setGameView(); //!< Sets the view of the window to the Game view
	sf::View& getGameView(); //!< Returns a reference the game view
	WindowInfo& getWindowInfo(); //!< Returns a reference to the current window's info
};
#endif