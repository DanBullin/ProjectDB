#include "Window.h"

/*! \file Window.cpp
* \brief CPP file for Window
*
* Implementation for a SFML window
*
*/

//! Constructor()
Window::Window()
{
	// Creates window based on window info
	create(sf::VideoMode(m_windowInfo.mk_WindowSize.x, m_windowInfo.mk_WindowSize.y), m_windowInfo.mk_titleText, sf::Style::Close);
	setVerticalSyncEnabled(m_windowInfo.m_enableVSync);
	setFramerateLimit(m_windowInfo.m_maxFramerate);
	// Set view's centre to 0,0 and size of 8,6 which is size of Box2D physics world
	m_view.setCenter(0, 0);
	m_view.setSize(8.f, 6.f);
	setView(m_view);
}

//! Destructor()
Window::~Window()
{

}

//! setGameView()
void Window::setGameView()
{
	setView(m_view);
}

/*!
\return a sf::View& - The game view
*/
sf::View& Window::getGameView()
{
	return m_view;
}

/*!
\return a WindowInfo& - The window's info
*/
WindowInfo& Window::getWindowInfo()
{
	return m_windowInfo;
}