#include "Events/EventListener.h"
#include "Game.h"

/*! \file EventListener.cpp
* \brief CPP file for EventListener
*
* Implementation for an EventListener
*
*/

// Initial values
bool EventListener::m_InstanceFlag = false;
EventListener* EventListener::m_eventListener = nullptr;

//! Constructor()
EventListener::EventListener()
{

}

/*!
\return a EventListener* - A pointer to the event listener instance
*/
EventListener* EventListener::getInstance()
{
	if (!m_InstanceFlag)
	{
		// If an instance hasn't been created, create one
		m_eventListener = new EventListener;
		// Prevent making more
		m_InstanceFlag = true;
		return m_eventListener;
	}
	return m_eventListener;
}

//! Destructor()
EventListener::~EventListener()
{
	// Clear all subscription objects
	m_subscribedObjects.clear();
	// Set all relevant pointers to null
	m_activeObject = nullptr;
	m_InstanceFlag = false;
	// Delete the listener but it happens at end of program life so didnt really matter
	delete m_eventListener;
	m_eventListener = nullptr;
}

/*!
\param object a GameObject* - A pointer to the object to subscribe
*/
void EventListener::attach(GameObject* object)
{
	m_subscribedObjects.push_back(object);
}

/*!
\param object a GameObject* - A pointer to the object to unsubscribe
*/
void EventListener::detach(GameObject* object)
{
	// Erase the object
	m_subscribedObjects.erase(remove(m_subscribedObjects.begin(), m_subscribedObjects.end(), object), m_subscribedObjects.end());
	// If the active object was this object, set active to null to prevent hidious consequences
	if (m_activeObject == object)
	{
		m_activeObject = nullptr;
	}
}

/*!
\param game a Game* - A pointer to the game
\param eventType a const int - The event type
\param mousePos a const sf::Vector2f - The mouse position converted to view coords
*/
void EventListener::notify(Game* game, const int eventType, const sf::Vector2f mousePos)
{
	// Start from the end and work the way to the front, this is because of order of layering
	// If two objects overlap, only want to trigger the top most object because that will be the object the user is interacting with
	for (auto i = m_subscribedObjects.rbegin(); i != m_subscribedObjects.rend(); ++i)
	{
		// If the event was a mouse move
		if (eventType == sf::Event::MouseMoved)
		{
			// If the object contains the mouse
			if ((*i)->contains(mousePos))
			{
				// and if that object is NOT the active object
				if (m_activeObject != *i)
				{
					// Set it as the active object and trigger old object its mouseLeave function
					if (m_activeObject != nullptr) { m_activeObject->mouseLeave(game); };
					m_activeObject = *i;
					// Trigger new active object's mouse enter function
					m_activeObject->mouseEnter(game);
					// Seeing as only input input happens at a time, we've done our input so no pointer processing below
					return;
				}
				return;
			}
		}
		// If the event was a mouse press
		else if (eventType == sf::Event::MouseButtonPressed)
		{
			// If we have an active object
			if (m_activeObject != nullptr)
			{
				// Trigger it's mouse press function
				// Mouse movement sets the active object for us
				m_activeObject->mousePress(game);
			}
			return;
		}
		// If the event was a mouse release
		else if (eventType == sf::Event::MouseButtonReleased)
		{
			// If we have an active object
			if (m_activeObject != nullptr)
			{
				// Trigger it's mouse release function
				// Mouse movement sets the active object for us
				m_activeObject->mouseRelease(game);
			}
			return;
		}
	}

	// If no mouse input succeeded, trigger the only event left which is if we have an active object, remove it
	if (m_activeObject != nullptr)
	{
		m_activeObject->mouseLeave(game);
		m_activeObject = nullptr;
	}
}

/*!
\param game a Game* - A pointer to the game
\param eventType a const int - The event type
\param key a const int - The key pressed/released
*/
void EventListener::notify(Game* game, const int eventType, const int key)
{
	// If a key was pressed
	if (eventType == sf::Event::KeyPressed)
	{
		// and the key isn't a key already pressed
		if (!keyAlreadyExists(key))
		{
			// Add the key to the active key list
			m_keysActive.push_back(key);
		}
	}
	// If a key was released
	else if (eventType == sf::Event::KeyReleased)
	{
		// Notify all subscribing objects of the key released
		for (auto g : m_subscribedObjects)
		{
			g->keyRelease(game, key);
		}
		// Erase key from list
		eraseKey(key);

		// If the tab key was released, show/unshow debug draw
		if (key == sf::Keyboard::Tab)
		{
			Level* tmp = static_cast<Level*>(game->getCurrentScene());
			tmp->setPhysicsDraw(!tmp->getPhysicsDraw());
		}
	}
}

/*!
\param game a Game* - A pointer to the game
*/
void EventListener::update(Game* game)
{
	// For all keys pressed
	for (auto k : m_keysActive)
	{
		// and for all subscribing objects
		for (auto g : m_subscribedObjects)
		{
			// send the object all active keys
			g->keyPress(game, k);
		}
	}
}

//! clearSubscriptions()
void EventListener::clearSubscriptions()
{
	// Clears all objects
	m_subscribedObjects.clear();
}

/*!
\param key a const int - The key to check if exists
\return a bool - A bool which represents whether the key passed exists
*/
bool EventListener::keyAlreadyExists(const int key)
{
	// Check if active key list contains the key passed
	std::vector<int>::iterator it = std::find(m_keysActive.begin(), m_keysActive.end(), key);
	if (it == m_keysActive.end())
	{
		// If it reaches the end of the list, key wasn't found
		return false;
	}
	return true;
}

/*!
\param key a const int - The key to erase
*/
void EventListener::eraseKey(const int key)
{
	// Erase the key passed if it exists in the list
	m_keysActive.erase(remove(m_keysActive.begin(), m_keysActive.end(), key), m_keysActive.end());
}