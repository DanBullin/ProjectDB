#include "GameObjects/GameObject.h"
#include "Events/EventListener.h"

/*! \file GameObject.cpp
* \brief CPP file for GameObject
*
* Implementation for GameObject
*
*/

//! Constructor()
GameObject::GameObject()
{
	// Set initial properties
	m_draw = true;
	m_enabled = true;
	m_markedDeletion = false;
}

//! Destructor()
GameObject::~GameObject()
{
	//LOG("Deleting object: " + m_name);
	// Detach from the event listener
	EventListener::getInstance()->detach(this);
	// Delete the SFML drawable
	delete m_drawable;
}

/*!
\return a std::string - The name of the object
*/
std::string GameObject::getName() const
{
	return m_name;
}

/*!
\param draw a const bool - Draw the object
*/
void GameObject::setDraw(const bool draw)
{
	m_draw = draw;
}

/*!
\return a bool - Should the object be drawn
*/
bool GameObject::getDraw() const
{
	return m_draw;
}

/*!
\return a bool - Is the object animated
*/
bool GameObject::getAnimated() const
{
	return m_animated;
}

/*!
\param enable a const bool - Enable the object
*/
void GameObject::setEnabled(const bool enable)
{
	m_enabled = enable;
}

/*!
\return a bool - Is the object enabled
*/
bool GameObject::getEnabled() const
{
	return m_enabled;
}

/*!
\param destroy a const bool - Destroy the object
*/
void GameObject::scheduleForDeletion(const bool destroy)
{
	m_markedDeletion = destroy;
}

/*!
\return a bool - Is the object scheduled for deletion
*/
bool GameObject::getScheduleForDeletion() const
{
	return m_markedDeletion;
}

/*!
\return a sf::Drawable* - The SFML drawable component
*/
sf::Drawable* GameObject::getDrawable()
{
	return m_drawable;
}

/*!
\param target a sf::RenderTarget & - A reference to the RenderTarget
\param states a sf::RenderStates - A render state
*/
void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_drawable);
}

/*!
\param game a Game* - A pointer to the game
*/
void GameObject::mouseEnter(Game * game)
{
}

/*!
\param game a Game* - A pointer to the game
*/
void GameObject::mouseLeave(Game * game)
{
}

/*!
\param game a Game* - A pointer to the game
*/
void GameObject::mousePress(Game * game)
{
}

/*!
\param game a Game* - A pointer to the game
*/
void GameObject::mouseRelease(Game * game)
{
}

/*!
\param game a Game* - A pointer to the game
\param key a const int - The key pressed
*/
void GameObject::keyPress(Game * game, const int key)
{
}

/*!
\param game a Game* - A pointer to the game
\param key a const int - The key released
*/
void GameObject::keyRelease(Game * game, const int key)
{
}

//! animationUpdate()
void GameObject::animationUpdate()
{
}